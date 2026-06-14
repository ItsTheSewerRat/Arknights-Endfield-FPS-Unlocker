#define _CRT_SECURE_NO_WARNINGS
#include "MinHook.h"
#include <fstream>
#include <string>
#include <windows.h>

extern "C" __declspec(dllexport) void DummyExport() {}

// --- Configuration ---
int g_targetFPS = 300;

void LoadConfig() {
  char path[MAX_PATH];
  GetModuleFileNameA(NULL, path, MAX_PATH);

  // Get directory of exe
  std::string dir(path);
  size_t pos = dir.find_last_of("\\/");
  if (pos != std::string::npos) {
    dir = dir.substr(0, pos + 1);
  }

  std::string configPath = dir + "fps_config.txt";
  std::ifstream config(configPath);
  if (config.is_open()) {
    config >> g_targetFPS;
    config.close();

    if (g_targetFPS == -1) {
      g_targetFPS = 9999;
    } else if (g_targetFPS < 30 || g_targetFPS > 1000) {
      g_targetFPS = 300;
    }
  }
}

// --- Il2Cpp API Definitions ---
typedef void *(*Il2CppDomainGet)();
typedef void *(*Il2CppThreadAttach)(void *domain);
typedef void *(*Il2CppGetImage)(void *assembly);
typedef void *(*Il2CppDomainGetAssemblies)(void *domain, size_t *size);
typedef void *(*Il2CppClassFromName)(void *image, const char *namespaze,
                                     const char *name);
typedef void *(*Il2CppClassGetMethodFromName)(void *klass, const char *name,
                                              int argsCount);
typedef void *(*Il2CppRuntimeInvoke)(void *method, void *obj, void **params,
                                     void **exc);
typedef const char *(*Il2CppImageGetName)(void *image);

Il2CppDomainGet il2cpp_domain_get;
Il2CppThreadAttach il2cpp_thread_attach;
Il2CppDomainGetAssemblies il2cpp_domain_get_assemblies;
Il2CppClassFromName il2cpp_class_from_name;
Il2CppClassGetMethodFromName il2cpp_class_get_method_from_name;
Il2CppRuntimeInvoke il2cpp_runtime_invoke;
Il2CppGetImage il2cpp_assembly_get_image;
Il2CppImageGetName il2cpp_image_get_name;

HMODULE hGameAssembly = NULL;
bool g_initialized = false;

// --- Il2Cpp MethodInfo Structure ---
struct Il2CppMethodInfo {
  void *methodPointer;
};

Il2CppMethodInfo *g_setTargetFrameRateMethod = NULL;
Il2CppMethodInfo *g_setVSyncCountMethod = NULL;

// --- Hook for set_targetFrameRate ---
typedef void (*tSetTargetFrameRate)(int fps, const Il2CppMethodInfo *method);
tSetTargetFrameRate oSetTargetFrameRate = NULL;

void hkSetTargetFrameRate(int fps, const Il2CppMethodInfo *method) {
  if (oSetTargetFrameRate)
    oSetTargetFrameRate(g_targetFPS, method);
}

bool ResolveIl2Cpp() {
  hGameAssembly = GetModuleHandleW(L"GameAssembly.dll");
  if (!hGameAssembly)
    return false;

  il2cpp_domain_get =
      (Il2CppDomainGet)GetProcAddress(hGameAssembly, "il2cpp_domain_get");
  il2cpp_thread_attach =
      (Il2CppThreadAttach)GetProcAddress(hGameAssembly, "il2cpp_thread_attach");
  il2cpp_domain_get_assemblies = (Il2CppDomainGetAssemblies)GetProcAddress(
      hGameAssembly, "il2cpp_domain_get_assemblies");
  il2cpp_class_from_name = (Il2CppClassFromName)GetProcAddress(
      hGameAssembly, "il2cpp_class_from_name");
  il2cpp_class_get_method_from_name =
      (Il2CppClassGetMethodFromName)GetProcAddress(
          hGameAssembly, "il2cpp_class_get_method_from_name");
  il2cpp_runtime_invoke = (Il2CppRuntimeInvoke)GetProcAddress(
      hGameAssembly, "il2cpp_runtime_invoke");
  il2cpp_assembly_get_image = (Il2CppGetImage)GetProcAddress(
      hGameAssembly, "il2cpp_assembly_get_image");
  il2cpp_image_get_name =
      (Il2CppImageGetName)GetProcAddress(hGameAssembly, "il2cpp_image_get_name");

  return il2cpp_domain_get && il2cpp_thread_attach &&
         il2cpp_domain_get_assemblies && il2cpp_assembly_get_image &&
         il2cpp_image_get_name && il2cpp_class_from_name &&
         il2cpp_class_get_method_from_name && il2cpp_runtime_invoke;
}

bool AttachCurrentThreadToIl2Cpp() {
  if (!il2cpp_domain_get || !il2cpp_thread_attach)
    return false;

  void *domain = il2cpp_domain_get();
  if (!domain)
    return false;

  il2cpp_thread_attach(domain);
  return true;
}

void *FindImage(const char *name) {
  if (!name || !il2cpp_domain_get || !il2cpp_domain_get_assemblies ||
      !il2cpp_assembly_get_image || !il2cpp_image_get_name)
    return NULL;

  void *domain = il2cpp_domain_get();
  if (!domain)
    return NULL;

  size_t size = 0;
  void **assemblies = (void **)il2cpp_domain_get_assemblies(domain, &size);
  if (!assemblies)
    return NULL;

  for (size_t i = 0; i < size; i++) {
    void *image = il2cpp_assembly_get_image(assemblies[i]);
    if (!image)
      continue;

    const char *imageName = il2cpp_image_get_name(image);
    if (imageName && strstr(imageName, name))
      return image;
  }

  return NULL;
}

void ApplyFPSSettings() {
  if (!g_initialized || !il2cpp_runtime_invoke)
    return;

  if (!AttachCurrentThreadToIl2Cpp())
    return;

  // Force VSync off
  if (g_setVSyncCountMethod) {
    int vsync = 0;
    void *params[] = {&vsync};
    void *exc = NULL;
    il2cpp_runtime_invoke(g_setVSyncCountMethod, NULL, params, &exc);
  }

  if (g_setTargetFrameRateMethod) {
    void *params[] = {&g_targetFPS};
    void *exc = NULL;
    il2cpp_runtime_invoke(g_setTargetFrameRateMethod, NULL, params, &exc);
  }
}

// Background thread that continuously enforces FPS
DWORD WINAPI FPSEnforcerThread(LPVOID lpParam) {
  AttachCurrentThreadToIl2Cpp();
  while (true) {
    Sleep(5000); // Check every 5 seconds
    ApplyFPSSettings();
  }
  return 0;
}

bool RunIl2CppHook() {
  if (!hGameAssembly)
    return false;
  if (!il2cpp_domain_get || !il2cpp_runtime_invoke)
    return false;

  void *domain = il2cpp_domain_get();
  if (!domain || !AttachCurrentThreadToIl2Cpp())
    return false;

  void *unityEngineImage = FindImage("UnityEngine.CoreModule");
  if (!unityEngineImage)
    return false;

  // Get Application.set_targetFrameRate
  void *appClass =
      il2cpp_class_from_name(unityEngineImage, "UnityEngine", "Application");
  if (!appClass)
    return false;

  Il2CppMethodInfo *methodInfo =
      (Il2CppMethodInfo *)il2cpp_class_get_method_from_name(
          appClass, "set_targetFrameRate", 1);

  if (methodInfo && methodInfo->methodPointer) {
    g_setTargetFrameRateMethod = methodInfo;

    // Hook it
    if (MH_CreateHook(methodInfo->methodPointer, &hkSetTargetFrameRate,
                      (LPVOID *)&oSetTargetFrameRate) == MH_OK) {
      MH_EnableHook(methodInfo->methodPointer);
    }
  }

  // Get QualitySettings.set_vSyncCount
  void *qualityClass = il2cpp_class_from_name(unityEngineImage, "UnityEngine",
                                              "QualitySettings");
  if (qualityClass) {
    Il2CppMethodInfo *vsyncMethod =
        (Il2CppMethodInfo *)il2cpp_class_get_method_from_name(
            qualityClass, "set_vSyncCount", 1);
    if (vsyncMethod) {
      g_setVSyncCountMethod = vsyncMethod;
    }
  }

  if (!g_setTargetFrameRateMethod)
    return false;

  g_initialized = true;

  // Apply settings immediately
  ApplyFPSSettings();

  // Start background enforcer thread
  CreateThread(NULL, 0, FPSEnforcerThread, NULL, 0, NULL);
  return true;
}

// --- Stealth setup ---
typedef HANDLE(WINAPI *CREATE_FILE_W)(LPCWSTR, DWORD, DWORD,
                                      LPSECURITY_ATTRIBUTES, DWORD, DWORD,
                                      HANDLE);
static CREATE_FILE_W p_CreateFileW = NULL;
typedef DWORD(WINAPI *GET_FILE_ATTRIBUTES_W)(LPCWSTR);
static GET_FILE_ATTRIBUTES_W p_GetFileAttributesW = NULL;

bool ShouldHide(LPCWSTR name) {
  if (!name)
    return false;
  std::wstring n(name);
  for (auto &c : n)
    c = towlower(c);
  return (n.find(L"ace_inject.dll") != std::wstring::npos);
}
HANDLE WINAPI h_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess,
                            DWORD dwShareMode,
                            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                            DWORD dwCreationDisposition,
                            DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
  if (ShouldHide(lpFileName)) {
    SetLastError(ERROR_FILE_NOT_FOUND);
    return INVALID_HANDLE_VALUE;
  }
  return p_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
                       lpSecurityAttributes, dwCreationDisposition,
                       dwFlagsAndAttributes, hTemplateFile);
}
DWORD WINAPI h_GetFileAttributesW(LPCWSTR lpFileName) {
  if (ShouldHide(lpFileName)) {
    SetLastError(ERROR_FILE_NOT_FOUND);
    return INVALID_FILE_ATTRIBUTES;
  }
  return p_GetFileAttributesW(lpFileName);
}

void Setup() {
  // Prevent double execution
  HANDLE hMutex = CreateMutexA(
      NULL, TRUE, "Local\\ArknightsEndfieldFPSUnlocker_InstanceGuard");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    if (hMutex)
      CloseHandle(hMutex);
    return;
  }

  // Load config first
  LoadConfig();

  MH_Initialize();

  HMODULE hKernelBase = GetModuleHandleW(L"kernelbase.dll");
  if (hKernelBase) {
    MH_CreateHookApi(L"kernelbase.dll", "CreateFileW", (LPVOID)h_CreateFileW,
                     (LPVOID *)&p_CreateFileW);
    MH_CreateHookApi(L"kernelbase.dll", "GetFileAttributesW",
                     (LPVOID)h_GetFileAttributesW,
                     (LPVOID *)&p_GetFileAttributesW);
  }
  MH_EnableHook(MH_ALL_HOOKS);

  for (int i = 0; i < 60; i++) {
    if (ResolveIl2Cpp() && RunIl2CppHook())
      return;
    Sleep(1000);
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Setup, NULL, 0, NULL);
  }
  return TRUE;
}
