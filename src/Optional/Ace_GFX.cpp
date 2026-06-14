#define _CRT_SECURE_NO_WARNINGS
#include <cstdarg>
#include <cstdint>
#include <math.h>
#include <stdio.h>
#include <string>
#include <windows.h>

extern "C" __declspec(dllexport) void Ace_GFX_Dummy() {}

#define INIT_DELAY_MS 10000
#define APPLY_INTERVAL_MS 5000
#define DEFAULT_LIVE_EDIT_INTERVAL_MS 1000

#define IL2CPP_OBJECT_HEADER_SIZE 0x10

typedef void *Il2CppDomain;
typedef void *Il2CppAssembly;
typedef void *Il2CppImage;
typedef void *Il2CppClass;
typedef void *Il2CppMethodInfo;
typedef void *Il2CppObject;
struct MethodInfo {
  void *methodPointer;
};

typedef Il2CppDomain (*fn_il2cpp_domain_get)();
typedef void *(*fn_il2cpp_thread_attach)(Il2CppDomain);
typedef void **(*fn_il2cpp_domain_get_assemblies)(Il2CppDomain, size_t *);
typedef Il2CppImage (*fn_il2cpp_assembly_get_image)(Il2CppAssembly);
typedef const char *(*fn_il2cpp_image_get_name)(Il2CppImage);
typedef Il2CppClass (*fn_il2cpp_class_from_name)(Il2CppImage, const char *,
                                                 const char *);
typedef Il2CppMethodInfo (*fn_il2cpp_class_get_method_from_name)(Il2CppClass,
                                                                 const char *,
                                                                 int);
typedef void *(*fn_il2cpp_class_get_field_from_name)(Il2CppClass,
                                                     const char *);
typedef void (*fn_il2cpp_field_static_get_value)(void *, void *);
typedef void (*fn_il2cpp_field_static_set_value)(void *, void *);
typedef void (*fn_il2cpp_field_get_value)(void *, void *, void *);
typedef void (*fn_il2cpp_field_set_value)(void *, void *, void *);
typedef size_t (*fn_il2cpp_field_get_offset)(void *);
typedef void *(*fn_il2cpp_class_get_fields)(Il2CppClass, void **);
typedef const char *(*fn_il2cpp_field_get_name)(void *);
typedef int (*fn_il2cpp_field_get_flags)(void *);
typedef Il2CppClass (*fn_il2cpp_class_get_parent)(Il2CppClass);
typedef Il2CppClass (*fn_il2cpp_object_get_class)(void *);
typedef void *(*fn_il2cpp_class_get_type)(Il2CppClass);
typedef void *(*fn_il2cpp_type_get_object)(void *);
typedef void *(*fn_il2cpp_runtime_invoke)(Il2CppMethodInfo, void *, void **, void **);

static fn_il2cpp_domain_get il2cpp_domain_get = nullptr;
static fn_il2cpp_thread_attach il2cpp_thread_attach = nullptr;
static fn_il2cpp_domain_get_assemblies il2cpp_domain_get_assemblies = nullptr;
static fn_il2cpp_assembly_get_image il2cpp_assembly_get_image = nullptr;
static fn_il2cpp_image_get_name il2cpp_image_get_name = nullptr;
static fn_il2cpp_class_from_name il2cpp_class_from_name = nullptr;
static fn_il2cpp_class_get_method_from_name il2cpp_class_get_method_from_name =
    nullptr;
static fn_il2cpp_class_get_field_from_name il2cpp_class_get_field_from_name =
    nullptr;
static fn_il2cpp_field_static_get_value il2cpp_field_static_get_value = nullptr;
static fn_il2cpp_field_static_set_value il2cpp_field_static_set_value = nullptr;
static fn_il2cpp_field_get_value il2cpp_field_get_value = nullptr;
static fn_il2cpp_field_set_value il2cpp_field_set_value = nullptr;
static fn_il2cpp_field_get_offset il2cpp_field_get_offset = nullptr;
static fn_il2cpp_class_get_fields il2cpp_class_get_fields = nullptr;
static fn_il2cpp_field_get_name il2cpp_field_get_name = nullptr;
static fn_il2cpp_field_get_flags il2cpp_field_get_flags = nullptr;
static fn_il2cpp_class_get_parent il2cpp_class_get_parent = nullptr;
static fn_il2cpp_object_get_class il2cpp_object_get_class = nullptr;
static fn_il2cpp_class_get_type il2cpp_class_get_type = nullptr;
static fn_il2cpp_type_get_object il2cpp_type_get_object = nullptr;
static fn_il2cpp_runtime_invoke il2cpp_runtime_invoke = nullptr;

#define FIELD_ATTRIBUTE_STATIC 0x0010

Il2CppImage FindImage(const char *name);
void *GetMethodPointer(Il2CppMethodInfo mi);

static HMODULE g_hGameAssembly = nullptr;
static HMODULE g_hSelfModule = nullptr;
static bool g_initialized = false;
static int g_screenWidth = 0, g_screenHeight = 0;
static bool g_gtaoPatched = false;
static bool g_shadowPatched = false;
static int g_patchCount = 0;
static float g_gtaoScale = -1.0f;
static float g_csmShadowSoftness = -1.0f;
static int g_csmShadowRes = -1;
static int g_charShadowRes = -1;
static int g_punctualShadowRes = -1;
static int g_asmShadowRes = -1;
static int g_csmShadowSampleMode = -1;
static int g_charShadowSampleMode = -1;
static float g_csmDepthBias = -1.0f;
static float g_csmNormalBias = -1.0f;
static float g_csmIntensity = -1.0f;
static float g_contactShadowIntensity = -1.0f;
static float g_contactShadowThickness = -1.0f;
static float g_contactShadowBilinear = -1.0f;
static float g_contactShadowContract = -1.0f;
static int g_screenSpaceShadowMask = -1;
static int g_aaMode = 1;
static int g_smaaQuality = -1;
static int g_ssrQuality = -1;
static int g_ssrEnable = -1;
static int g_ssrSampleCount = -1;
static int g_ssrUpsampling = -1;
static float g_renderScale = -1.0f;
static int g_anisoLevel = -1;
static float g_sharpening = -1.0f;
static int g_logging = 1;
static int g_liveEdit = 0;
static int g_liveEditIntervalMs = DEFAULT_LIVE_EDIT_INTERVAL_MS;

static char g_iniPath[MAX_PATH] = {0};
static char g_logPath[MAX_PATH] = {0};
static FILETIME g_configLastWriteTime = {0};
static bool g_configLastWriteTimeValid = false;

struct RenderHookOffsets {
  size_t renderParamsGtaoPtr;
  size_t gtaoScreenWidth;
  size_t gtaoScreenHeight;
  size_t beforeCullingShadowConfigPtr;
  size_t shadowCsmDepthBias;
  size_t shadowCsmNormalBias;
  size_t shadowCsmIntensity;
  size_t shadowCsmSoftness;
  size_t shadowContactIntensity;
  size_t shadowContactThickness;
  size_t shadowContactBilinear;
  size_t shadowContactContract;
};

static RenderHookOffsets g_renderHookOffsets = {};
static bool g_renderHookOffsetsResolved = false;

struct GfxConfigSnapshot {
  int logging;
  int liveEdit;
  int liveEditIntervalMs;
  float gtaoScale;
  float csmShadowSoftness;
  int csmShadowRes;
  int charShadowRes;
  int punctualShadowRes;
  int asmShadowRes;
  int screenSpaceShadowMask;
  int csmShadowSampleMode;
  int charShadowSampleMode;
  float csmDepthBias;
  float csmNormalBias;
  float csmIntensity;
  float contactShadowIntensity;
  float contactShadowThickness;
  float contactShadowBilinear;
  float contactShadowContract;
  int aaMode;
  int smaaQuality;
  int ssrQuality;
  int ssrEnable;
  int ssrSampleCount;
  int ssrUpsampling;
  float renderScale;
  int anisoLevel;
  float sharpening;
};

struct IntWriteInfo {
  uintptr_t ownerPtr;
  uintptr_t settingParamPtr;
  uintptr_t valueAddr;
  size_t targetOffset;
  size_t valueOffset;
  int oldValue;
  int newValue;
  bool changed;
};

struct FloatWriteInfo {
  uintptr_t ownerPtr;
  uintptr_t settingParamPtr;
  uintptr_t valueAddr;
  size_t targetOffset;
  size_t valueOffset;
  float oldValue;
  float newValue;
  bool changed;
};

struct CameraAAWriteInfo {
  uint32_t cameraCount;
  uint32_t changedCount;
  uintptr_t firstChangedCamera;
  uint32_t fieldOffset;
  int firstOldValue;
  int newValue;
};

struct SMAAWriteInfo {
  uintptr_t smaaInstance;
  uintptr_t valueAddr;
  size_t valueOffset;
  int oldValue;
  int newValue;
  bool changed;
};

struct AnisoWriteInfo {
  void *methodPtr;
  const char *methodName;
  int level;
};

static bool g_logNextGTAOApply = false;
static bool g_logNextCsmShadowSoftnessApply = false;
static bool g_logNextCsmDepthBiasApply = false;
static bool g_logNextCsmNormalBiasApply = false;
static bool g_logNextCsmIntensityApply = false;
static bool g_logNextContactShadowIntensityApply = false;
static bool g_logNextContactShadowThicknessApply = false;
static bool g_logNextContactShadowBilinearApply = false;
static bool g_logNextContactShadowContractApply = false;
static int32_t g_gtaoOriginalWidth = -1;
static int32_t g_gtaoOriginalHeight = -1;
static int32_t g_gtaoPreviousWidth = -1;
static int32_t g_gtaoPreviousHeight = -1;

typedef void *(*ConvertSettingParamsToCpp_t)(void *settingParameters);
static ConvertSettingParamsToCpp_t g_TrampolineFunc = nullptr;
static void *g_pTrampoline = nullptr;
static void *g_ConvertMethodPtr = nullptr;
static uint8_t g_OriginalBytes[16] = {0};
static bool g_HookInstalled = false;

bool IsMainGameProcess() {
  char exePath[MAX_PATH];
  GetModuleFileNameA(NULL, exePath, MAX_PATH);
  return strstr(exePath, "EndlessField.exe") != nullptr ||
         strstr(exePath, "Endfield.exe") != nullptr;
}

std::string GetGameDirectory() {
  char exePath[MAX_PATH] = {0};
  GetModuleFileNameA(NULL, exePath, MAX_PATH);
  std::string dir(exePath);
  size_t lastSlash = dir.rfind('\\');
  if (lastSlash != std::string::npos)
    dir = dir.substr(0, lastSlash + 1);
  return dir;
}

std::string GetExecutablePath() {
  char exePath[MAX_PATH] = {0};
  GetModuleFileNameA(NULL, exePath, MAX_PATH);
  return std::string(exePath);
}

std::string GetSelfModulePath() {
  char modulePath[MAX_PATH] = {0};
  GetModuleFileNameA(g_hSelfModule, modulePath, MAX_PATH);
  return std::string(modulePath);
}

void InitLogPath() {
  if (g_logPath[0] != '\0')
    return;

  std::string logPath = GetGameDirectory() + "EndfieldGFX.log";
  strncpy(g_logPath, logPath.c_str(), MAX_PATH - 1);
  g_logPath[MAX_PATH - 1] = '\0';
}

void ResetLogFile() {
  if (!g_logging)
    return;

  InitLogPath();
  FILE *file = fopen(g_logPath, "w");
  if (!file)
    return;

  SYSTEMTIME st = {};
  GetLocalTime(&st);
  fprintf(file,
          "=== EndfieldGFX.log started %04u-%02u-%02u %02u:%02u:%02u ===\n",
          st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
  fprintf(file, "ProcessId=%lu ThreadId=%lu\n", GetCurrentProcessId(),
          GetCurrentThreadId());
  fprintf(file, "Executable=%s\n", GetExecutablePath().c_str());
  fprintf(file, "Module=%s\n", GetSelfModulePath().c_str());
  fclose(file);
}

void CreateDebugConsole() {}

void Log(const char *fmt, ...) {
  if (!g_logging || !fmt)
    return;

  InitLogPath();
  FILE *file = fopen(g_logPath, "a");
  if (!file)
    return;

  SYSTEMTIME st = {};
  GetLocalTime(&st);
  fprintf(file, "[%02u:%02u:%02u] ", st.wHour, st.wMinute, st.wSecond);

  va_list args;
  va_start(args, fmt);
  vfprintf(file, fmt, args);
  va_end(args);

  fputc('\n', file);
  fclose(file);
}

void LogColored(WORD, const char *fmt, ...) {
  if (!g_logging || !fmt)
    return;

  char buffer[1024];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  buffer[sizeof(buffer) - 1] = '\0';
  Log("%s", buffer);
}

#define LOG_SUCCESS(...) do { Log("[OK] " __VA_ARGS__); } while (0)
#define LOG_WARNING(...) do { Log("[WARN] " __VA_ARGS__); } while (0)
#define LOG_ERROR(...) do { Log("[ERROR] " __VA_ARGS__); } while (0)
#define LOG_INFO(...) do { Log("[INFO] " __VA_ARGS__); } while (0)

bool FloatChanged(float a, float b) {
  return fabsf(a - b) > 0.0001f;
}

bool HasPendingShadowApplyLog() {
  return g_logNextCsmShadowSoftnessApply || g_logNextCsmDepthBiasApply ||
         g_logNextCsmNormalBiasApply || g_logNextCsmIntensityApply ||
         g_logNextContactShadowIntensityApply ||
         g_logNextContactShadowThicknessApply ||
         g_logNextContactShadowBilinearApply ||
         g_logNextContactShadowContractApply;
}

void ClearPendingShadowApplyLogs() {
  g_logNextCsmShadowSoftnessApply = false;
  g_logNextCsmDepthBiasApply = false;
  g_logNextCsmNormalBiasApply = false;
  g_logNextCsmIntensityApply = false;
  g_logNextContactShadowIntensityApply = false;
  g_logNextContactShadowThicknessApply = false;
  g_logNextContactShadowBilinearApply = false;
  g_logNextContactShadowContractApply = false;
}

GfxConfigSnapshot CaptureConfigSnapshot() {
  GfxConfigSnapshot config = {};
  config.logging = g_logging;
  config.liveEdit = g_liveEdit;
  config.liveEditIntervalMs = g_liveEditIntervalMs;
  config.gtaoScale = g_gtaoScale;
  config.csmShadowSoftness = g_csmShadowSoftness;
  config.csmShadowRes = g_csmShadowRes;
  config.charShadowRes = g_charShadowRes;
  config.punctualShadowRes = g_punctualShadowRes;
  config.asmShadowRes = g_asmShadowRes;
  config.screenSpaceShadowMask = g_screenSpaceShadowMask;
  config.csmShadowSampleMode = g_csmShadowSampleMode;
  config.charShadowSampleMode = g_charShadowSampleMode;
  config.csmDepthBias = g_csmDepthBias;
  config.csmNormalBias = g_csmNormalBias;
  config.csmIntensity = g_csmIntensity;
  config.contactShadowIntensity = g_contactShadowIntensity;
  config.contactShadowThickness = g_contactShadowThickness;
  config.contactShadowBilinear = g_contactShadowBilinear;
  config.contactShadowContract = g_contactShadowContract;
  config.aaMode = g_aaMode;
  config.smaaQuality = g_smaaQuality;
  config.ssrQuality = g_ssrQuality;
  config.ssrEnable = g_ssrEnable;
  config.ssrSampleCount = g_ssrSampleCount;
  config.ssrUpsampling = g_ssrUpsampling;
  config.renderScale = g_renderScale;
  config.anisoLevel = g_anisoLevel;
  config.sharpening = g_sharpening;
  return config;
}

bool ShouldLogIntApply(int value, int oldValue, bool active, bool oldActive,
                       const GfxConfigSnapshot *before) {
  if (!before)
    return active;
  return active != oldActive || (active && value != oldValue);
}

bool ShouldLogFloatApply(float value, float oldValue, bool active,
                         bool oldActive, const GfxConfigSnapshot *before) {
  if (!before)
    return active;
  return active != oldActive || (active && FloatChanged(value, oldValue));
}

void LogConfigIntSetting(const char *name, int value, int oldValue,
                         bool active, bool oldActive,
                         const GfxConfigSnapshot *before, int *loggedCount) {
  if (!before) {
    if (active) {
      Log("    %s = %d", name, value);
      (*loggedCount)++;
    }
    return;
  }

  if (!ShouldLogIntApply(value, oldValue, active, oldActive, before))
    return;

  if (active && oldActive)
    Log("    %s: %d -> %d", name, oldValue, value);
  else if (active)
    Log("    %s: disabled -> %d", name, value);
  else
    Log("    %s: %d -> disabled", name, oldValue);
  (*loggedCount)++;
}

void LogConfigFloatSetting(const char *name, float value, float oldValue,
                           bool active, bool oldActive,
                           const GfxConfigSnapshot *before, int *loggedCount) {
  if (!before) {
    if (active) {
      Log("    %s = %.3f", name, value);
      (*loggedCount)++;
    }
    return;
  }

  if (!ShouldLogFloatApply(value, oldValue, active, oldActive, before))
    return;

  if (active && oldActive)
    Log("    %s: %.3f -> %.3f", name, oldValue, value);
  else if (active)
    Log("    %s: disabled -> %.3f", name, value);
  else
    Log("    %s: %.3f -> disabled", name, oldValue);
  (*loggedCount)++;
}

void LogSettingDisabled(const char *settingName) {
  Log("%s apply:", settingName);
  Log("  configured: disabled");
  Log("  runtime write: skipped");
}

void LogIntWriteResult(const char *settingName, const char *fieldName, bool ok,
                       const IntWriteInfo &info) {
  Log("%s apply:", settingName);
  Log("  IL2CPP field: %s", fieldName);
  if (info.ownerPtr)
    Log("  owner pointer: %p", (void *)info.ownerPtr);
  if (info.settingParamPtr)
    Log("  setting parameter pointer: %p", (void *)info.settingParamPtr);
  if (info.targetOffset)
    Log("  field offset: 0x%zX", info.targetOffset);
  if (info.valueAddr)
    Log("  value address: %p", (void *)info.valueAddr);
  if (info.valueOffset)
    Log("  value field offset: 0x%zX", info.valueOffset);
  if (ok)
    Log("  value: %d -> %d (%s)", info.oldValue, info.newValue,
        info.changed ? "written" : "unchanged");
  Log("  result: %s", ok ? "OK" : "FAILED");
}

void LogFloatWriteResult(const char *settingName, const char *fieldName,
                         bool ok, const FloatWriteInfo &info) {
  Log("%s apply:", settingName);
  Log("  IL2CPP field: %s", fieldName);
  if (info.ownerPtr)
    Log("  owner pointer: %p", (void *)info.ownerPtr);
  if (info.settingParamPtr)
    Log("  setting parameter pointer: %p", (void *)info.settingParamPtr);
  if (info.targetOffset)
    Log("  field offset: 0x%zX", info.targetOffset);
  if (info.valueAddr)
    Log("  value address: %p", (void *)info.valueAddr);
  if (info.valueOffset)
    Log("  value field offset: 0x%zX", info.valueOffset);
  if (ok)
    Log("  value: %.3f -> %.3f (%s)", info.oldValue, info.newValue,
        info.changed ? "written" : "unchanged");
  Log("  result: %s", ok ? "OK" : "FAILED");
}

void LogCameraAAWriteResult(bool ok, const CameraAAWriteInfo &info) {
  Log("AA apply:");
  Log("  IL2CPP field: HG.Rendering.Runtime.HGAdditionalCameraData.antialiasing");
  if (info.fieldOffset)
    Log("  field offset: 0x%X", info.fieldOffset);
  Log("  cameras found: %u", info.cameraCount);
  Log("  cameras changed: %u", info.changedCount);
  if (info.firstChangedCamera)
    Log("  first changed camera: %p", (void *)info.firstChangedCamera);
  if (ok && info.changedCount > 0)
    Log("  first changed value: %d -> %d", info.firstOldValue, info.newValue);
  Log("  result: %s", ok ? "OK" : "FAILED");
}

void LogSMAAWriteResult(bool ok, const SMAAWriteInfo &info) {
  Log("SMAA apply:");
  Log("  IL2CPP field: HG.Rendering.Runtime.HGSMAA.s_instance");
  if (info.smaaInstance)
    Log("  instance pointer: %p", (void *)info.smaaInstance);
  if (info.valueAddr)
    Log("  value address: %p", (void *)info.valueAddr);
  if (info.valueOffset)
    Log("  mode offset: 0x%zX", info.valueOffset);
  if (ok)
    Log("  value: %d -> %d (%s)", info.oldValue, info.newValue,
        info.changed ? "written" : "unchanged");
  Log("  result: %s", ok ? "OK" : "FAILED");
}

void LogAnisoWriteResult(bool ok, const AnisoWriteInfo &info) {
  Log("AnisoLevel apply:");
  Log("  IL2CPP method: %s", info.methodName ? info.methodName : "not resolved");
  if (info.methodPtr)
    Log("  method pointer: %p", info.methodPtr);
  Log("  level: %d", info.level);
  Log("  result: %s", ok ? "OK" : "FAILED");
}

template <typename T> inline bool SafeRead(uintptr_t addr, T *out) {
  __try {
    if (addr < 0x10000 || addr > 0x00007FFFFFFFFFFF)
      return false;
    *out = *(T *)addr;
    return true;
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    return false;
  }
}

template <typename T> inline bool SafeWrite(uintptr_t addr, T val) {
  __try {
    if (addr < 0x10000 || addr > 0x00007FFFFFFFFFFF)
      return false;
    *(T *)addr = val;
    return true;
  } __except (EXCEPTION_EXECUTE_HANDLER) {
    return false;
  }
}

void *FindFieldByName(void *klass, const char *fieldName) {
  if (!klass || !fieldName || !il2cpp_class_get_fields || !il2cpp_field_get_name)
    return nullptr;

  std::string targetName(fieldName);
  std::string backingName = "<" + targetName + ">k__BackingField";

  void *currentClass = klass;
  while (currentClass) {
    void *iter = nullptr;
    while (void *field = il2cpp_class_get_fields(currentClass, &iter)) {
      const char *name = il2cpp_field_get_name(field);
      if (!name)
        continue;
      std::string fName(name);
      if (fName == targetName || fName == backingName) {
        return field;
      }
    }
    if (il2cpp_class_get_parent) {
      currentClass = il2cpp_class_get_parent(currentClass);
    } else {
      break;
    }
  }
  return nullptr;
}

Il2CppClass FindHGGraphicsClass(Il2CppImage image, const char *className) {
  if (!image || !className || !il2cpp_class_from_name)
    return nullptr;

  Il2CppClass klass = il2cpp_class_from_name(
      image, "UnityEngine.HyperGryphEngineCode", className);
  if (!klass)
    klass = il2cpp_class_from_name(image, "", className);
  return klass;
}

bool ResolveCppFieldOffset(Il2CppClass klass, const char *fieldName,
                           size_t *outOffset) {
  if (!klass || !fieldName || !outOffset || !il2cpp_field_get_offset)
    return false;

  void *field = FindFieldByName(klass, fieldName);
  if (!field)
    return false;

  size_t il2cppOffset = il2cpp_field_get_offset(field);
  if (il2cppOffset < IL2CPP_OBJECT_HEADER_SIZE)
    return false;

  *outOffset = il2cppOffset - IL2CPP_OBJECT_HEADER_SIZE;
  return true;
}

bool ResolveCppFieldOffsetAny(Il2CppClass klass, const char *const *fieldNames,
                              size_t fieldNameCount, size_t *outOffset) {
  for (size_t i = 0; i < fieldNameCount; i++) {
    if (ResolveCppFieldOffset(klass, fieldNames[i], outOffset))
      return true;
  }
  return false;
}

bool ResolveRenderHookOffsets() {
  if (g_renderHookOffsetsResolved)
    return true;

  Il2CppImage graphicsImage = FindImage("UnityEngine.HGGraphicsCPPModule");
  if (!graphicsImage) {
    Log("Render hook offsets: UnityEngine.HGGraphicsCPPModule not loaded");
    return false;
  }

  Il2CppClass renderParamsClass =
      FindHGGraphicsClass(graphicsImage, "HGRenderPathParamsCPP");
  Il2CppClass beforeCullingClass =
      FindHGGraphicsClass(graphicsImage, "HGRenderPathBeforeCullingParamsCPP");
  Il2CppClass gtaoClass = FindHGGraphicsClass(
      graphicsImage, "HGGTAmbientOcclusionSettingParameters");
  Il2CppClass shadowConfigClass =
      FindHGGraphicsClass(graphicsImage, "HGShadowConfigCPP");

  RenderHookOffsets offsets = {};
  bool success = true;
  const char *gtaoFieldNames[] = {"gtaoSettingParameters", "gtao"};
  const char *softnessFieldNames[] = {"csmShadowSoftness", "csmSoftness"};
  const char *thicknessFieldNames[] = {"contactShadowSurfaceThickness",
                                       "contactShadowThickness"};
  const char *bilinearFieldNames[] = {"contactShadowBilinearThreshold",
                                      "contactShadowBilinear"};

  success &= ResolveCppFieldOffsetAny(renderParamsClass, gtaoFieldNames, 2,
                                      &offsets.renderParamsGtaoPtr);
  success &= ResolveCppFieldOffset(
      beforeCullingClass, "shadowConfig",
      &offsets.beforeCullingShadowConfigPtr);
  success &= ResolveCppFieldOffset(gtaoClass, "screenWidth",
                                   &offsets.gtaoScreenWidth);
  success &= ResolveCppFieldOffset(gtaoClass, "screenHeight",
                                   &offsets.gtaoScreenHeight);
  success &= ResolveCppFieldOffset(shadowConfigClass, "csmDepthBias",
                                   &offsets.shadowCsmDepthBias);
  success &= ResolveCppFieldOffset(shadowConfigClass, "csmNormalBias",
                                   &offsets.shadowCsmNormalBias);
  success &= ResolveCppFieldOffset(shadowConfigClass, "csmIntensity",
                                   &offsets.shadowCsmIntensity);
  success &= ResolveCppFieldOffsetAny(shadowConfigClass, softnessFieldNames, 2,
                                      &offsets.shadowCsmSoftness);
  success &= ResolveCppFieldOffset(shadowConfigClass, "contactShadowIntensity",
                                   &offsets.shadowContactIntensity);
  success &= ResolveCppFieldOffsetAny(shadowConfigClass, thicknessFieldNames, 2,
                                      &offsets.shadowContactThickness);
  success &= ResolveCppFieldOffsetAny(shadowConfigClass, bilinearFieldNames, 2,
                                      &offsets.shadowContactBilinear);
  success &= ResolveCppFieldOffset(shadowConfigClass, "contactShadowContract",
                                   &offsets.shadowContactContract);

  if (!success) {
    Log("Render hook offsets: failed to resolve required metadata fields");
    return false;
  }

  g_renderHookOffsets = offsets;
  g_renderHookOffsetsResolved = true;
  Log("Render hook offsets: GTAO=0x%zX width=0x%zX height=0x%zX shadowConfig=0x%zX",
      offsets.renderParamsGtaoPtr, offsets.gtaoScreenWidth,
      offsets.gtaoScreenHeight, offsets.beforeCullingShadowConfigPtr);
  return true;
}

void *GetObjectClass(uintptr_t objAddr) {
  if (!il2cpp_object_get_class)
    return nullptr;
  return il2cpp_object_get_class((void *)objAddr);
}

bool SetSettingParameterValue(const char *settingName, int value,
                              IntWriteInfo *writeInfo = nullptr) {
  if (writeInfo)
    *writeInfo = {};

  if (!il2cpp_class_get_field_from_name || !il2cpp_field_static_get_value ||
      !il2cpp_field_get_offset)
    return false;

  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage)
    return false;

  Il2CppClass rpmClass = il2cpp_class_from_name(
      coreImage, "UnityEngine.Rendering", "RenderPipelineManager");
  if (!rpmClass)
    return false;

  void *pipelineField = il2cpp_class_get_field_from_name(rpmClass, "s_currentPipeline");
  if (!pipelineField)
    pipelineField = FindFieldByName(rpmClass, "s_currentPipeline");
  if (!pipelineField)
    return false;

  uintptr_t pipelinePtr = 0;
  il2cpp_field_static_get_value(pipelineField, &pipelinePtr);
  if (!pipelinePtr)
    return false;

  void *pipelineClass = GetObjectClass(pipelinePtr);
  if (!pipelineClass) {
    for (int o = 0; o < 0x200; o += 8) {
      uintptr_t p;
      if (SafeRead(pipelinePtr - o, &p) && p > 0x10000) {
        pipelineClass = (void *)p;
        break;
      }
    }
  }

  void *settingsField = FindFieldByName(pipelineClass, "settingParameters");
  if (!settingsField)
    return false;

  size_t settingsOffset = il2cpp_field_get_offset(settingsField);
  uintptr_t settingsPtr = 0;
  if (!SafeRead(pipelinePtr + settingsOffset, &settingsPtr) || !settingsPtr)
    return false;

  void *settingsClass = GetObjectClass(settingsPtr);
  if (!settingsClass) {
    for (int o = 0; o < 0x200; o += 8) {
      uintptr_t p;
      if (SafeRead(settingsPtr - o, &p) && p > 0x10000) {
        settingsClass = (void *)p;
        break;
      }
    }
  }

  void *targetField = FindFieldByName(settingsClass, settingName);
  if (!targetField)
    return false;

  size_t targetOffset = il2cpp_field_get_offset(targetField);
  uintptr_t settingParamPtr = 0;
  if (!SafeRead(settingsPtr + targetOffset, &settingParamPtr) || !settingParamPtr)
    return false;

  void *paramClass = GetObjectClass(settingParamPtr);
  if (!paramClass) {
    for (int o = 0; o < 0x100; o += 8) {
      uintptr_t p;
      if (SafeRead(settingParamPtr - o, &p) && p > 0x10000) {
        paramClass = (void *)p;
        break;
      }
    }
  }

  void *paramValueField = FindFieldByName(paramClass, "paramValue");
  if (!paramValueField)
    return false;

  size_t paramOffset = il2cpp_field_get_offset(paramValueField);
  uintptr_t valueAddr = settingParamPtr + paramOffset;

  int oldValue = 0;
  SafeRead(valueAddr, &oldValue);

  if (writeInfo) {
    writeInfo->ownerPtr = settingsPtr;
    writeInfo->settingParamPtr = settingParamPtr;
    writeInfo->valueAddr = valueAddr;
    writeInfo->targetOffset = targetOffset;
    writeInfo->valueOffset = paramOffset;
    writeInfo->oldValue = oldValue;
    writeInfo->newValue = value;
    writeInfo->changed = oldValue != value;
  }

  if (!SafeWrite(valueAddr, value))
    return false;

  return true;
}

bool SetShadowManagerValue(const char *fieldName, int value,
                           IntWriteInfo *writeInfo = nullptr) {
  if (writeInfo)
    *writeInfo = {};

  if (!fieldName || !il2cpp_class_get_field_from_name ||
      !il2cpp_field_static_get_value || !il2cpp_field_get_offset)
    return false;

  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage)
    return false;

  Il2CppClass rpmClass = il2cpp_class_from_name(
      coreImage, "UnityEngine.Rendering", "RenderPipelineManager");
  if (!rpmClass)
    return false;

  void *pipelineField = il2cpp_class_get_field_from_name(rpmClass, "s_currentPipeline");
  if (!pipelineField)
    pipelineField = FindFieldByName(rpmClass, "s_currentPipeline");
  if (!pipelineField)
    return false;

  uintptr_t pipelinePtr = 0;
  il2cpp_field_static_get_value(pipelineField, &pipelinePtr);
  if (!pipelinePtr)
    return false;

  void *pipelineClass = GetObjectClass(pipelinePtr);
  if (!pipelineClass)
    return false;

  void *shadowManagerField = FindFieldByName(pipelineClass, "shadowManager");
  if (!shadowManagerField)
    shadowManagerField = FindFieldByName(pipelineClass, "m_shadowManager");
  if (!shadowManagerField)
    shadowManagerField = FindFieldByName(pipelineClass, "m_ShadowManager");
  if (!shadowManagerField)
    return false;

  size_t shadowManagerOffset = il2cpp_field_get_offset(shadowManagerField);
  uintptr_t shadowManagerPtr = 0;
  if (!SafeRead(pipelinePtr + shadowManagerOffset, &shadowManagerPtr) ||
      !shadowManagerPtr)
    return false;

  void *shadowManagerClass = GetObjectClass(shadowManagerPtr);
  if (!shadowManagerClass)
    return false;

  void *targetField = FindFieldByName(shadowManagerClass, fieldName);
  if (!targetField)
    return false;

  size_t targetOffset = il2cpp_field_get_offset(targetField);
  uintptr_t valueAddr = shadowManagerPtr + targetOffset;
  int oldValue = 0;
  SafeRead(valueAddr, &oldValue);

  if (writeInfo) {
    writeInfo->ownerPtr = shadowManagerPtr;
    writeInfo->valueAddr = valueAddr;
    writeInfo->targetOffset = targetOffset;
    writeInfo->valueOffset = targetOffset;
    writeInfo->oldValue = oldValue;
    writeInfo->newValue = value;
    writeInfo->changed = oldValue != value;
  }

  return SafeWrite(valueAddr, value);
}

bool ApplyManagedShadowSettings(const GfxConfigSnapshot *before = nullptr) {
  bool success = true;

#define APPLY_SETTING_INT(configValue, beforeMember, configName, il2cppField, runtimeField) \
  do { \
    bool active = (configValue) >= 0; \
    bool oldActive = before ? before->beforeMember >= 0 : false; \
    int oldValue = before ? before->beforeMember : -1; \
    bool logThis = ShouldLogIntApply((configValue), oldValue, active, oldActive, before); \
    if (active) { \
      IntWriteInfo info; \
      bool ok = SetSettingParameterValue((runtimeField), (configValue), &info); \
      success &= ok; \
      if (logThis) \
        LogIntWriteResult((configName), (il2cppField), ok, info); \
    } else if (logThis) { \
      LogSettingDisabled((configName)); \
    } \
  } while (0)

  APPLY_SETTING_INT(g_csmShadowRes, csmShadowRes, "CSMShadowRes",
                    "HGSettingParameters.csmShadowMapTileResolution.paramValue",
                    "csmShadowMapTileResolution");
  APPLY_SETTING_INT(g_charShadowRes, charShadowRes, "CharacterShadowRes",
                    "HGSettingParameters.characterShadowMapResolution.paramValue",
                    "characterShadowMapResolution");
  APPLY_SETTING_INT(g_punctualShadowRes, punctualShadowRes,
                    "PunctualLightShadowRes",
                    "HGSettingParameters.punctualLightTileMaxSize.paramValue",
                    "punctualLightTileMaxSize");
  APPLY_SETTING_INT(g_asmShadowRes, asmShadowRes, "ASMShadowRes",
                    "HGSettingParameters.asmShadowMapTileResolution.paramValue",
                    "asmShadowMapTileResolution");

#undef APPLY_SETTING_INT

  bool sampleActive = g_csmShadowSampleMode >= 0;
  bool oldSampleActive = before ? before->csmShadowSampleMode >= 0 : false;
  int oldSampleValue = before ? before->csmShadowSampleMode : -1;
  bool logSample = ShouldLogIntApply(g_csmShadowSampleMode, oldSampleValue,
                                     sampleActive, oldSampleActive, before);
  if (sampleActive) {
    IntWriteInfo info;
    bool ok = SetShadowManagerValue("m_csmShadowSampleMode",
                                    g_csmShadowSampleMode, &info);
    success &= ok;
    if (logSample)
      LogIntWriteResult("CSMShadowSampleMode",
                        "HGShadowManager.m_csmShadowSampleMode", ok, info);
  } else if (logSample) {
    LogSettingDisabled("CSMShadowSampleMode");
  }

  return success;
}

static float g_ssrResScale = -1.0f;

void ApplySSRQualityPreset(int& ssrEnable, int& sampleCount, int& upsampling) {
  switch (g_ssrQuality) {
    case 0:
      ssrEnable = 0;
      break;
    case 1:
      ssrEnable = 1; sampleCount = 128; upsampling = 1;
      break;
    case 2:
      ssrEnable = 1; sampleCount = 192; upsampling = 1;
      break;
    case 3:
      ssrEnable = 1; sampleCount = 256; upsampling = 1;
      break;
    case 4:
      ssrEnable = 1; sampleCount = 512; upsampling = 0;
      g_ssrResScale = 1.0f;
      break;
    default:
      break;
  }
}

void ResolveSSRValues(int quality, int configuredEnable, int configuredSamples,
                      int configuredUpsampling, int *ssrEnable,
                      int *sampleCount, int *upsampling) {
  *ssrEnable = configuredEnable;
  *sampleCount = configuredSamples;
  *upsampling = configuredUpsampling;

  switch (quality) {
    case 0:
      *ssrEnable = 0;
      break;
    case 1:
      *ssrEnable = 1;
      *sampleCount = 128;
      *upsampling = 1;
      break;
    case 2:
      *ssrEnable = 1;
      *sampleCount = 192;
      *upsampling = 1;
      break;
    case 3:
      *ssrEnable = 1;
      *sampleCount = 256;
      *upsampling = 1;
      break;
    case 4:
      *ssrEnable = 1;
      *sampleCount = 512;
      *upsampling = 0;
      break;
    default:
      break;
  }

  if (configuredEnable >= 0)
    *ssrEnable = configuredEnable;
  if (configuredSamples >= 0)
    *sampleCount = configuredSamples;
  if (configuredUpsampling >= 0)
    *upsampling = configuredUpsampling;
}

bool SetSettingParameterFloatValue(const char *settingName, float value,
                                   FloatWriteInfo *writeInfo = nullptr) {
  if (writeInfo)
    *writeInfo = {};

  if (!il2cpp_class_get_field_from_name || !il2cpp_field_static_get_value ||
      !il2cpp_field_get_offset)
    return false;

  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage) return false;

  Il2CppClass rpmClass = il2cpp_class_from_name(
      coreImage, "UnityEngine.Rendering", "RenderPipelineManager");
  if (!rpmClass) return false;

  void *pipelineField = il2cpp_class_get_field_from_name(rpmClass, "s_currentPipeline");
  if (!pipelineField) pipelineField = FindFieldByName(rpmClass, "s_currentPipeline");
  if (!pipelineField) return false;

  uintptr_t pipelinePtr = 0;
  il2cpp_field_static_get_value(pipelineField, &pipelinePtr);
  if (!pipelinePtr) return false;

  void *pipelineClass = GetObjectClass(pipelinePtr);
  void *settingsField = FindFieldByName(pipelineClass, "settingParameters");
  if (!settingsField) return false;

  size_t settingsOffset = il2cpp_field_get_offset(settingsField);
  uintptr_t settingsPtr = 0;
  if (!SafeRead(pipelinePtr + settingsOffset, &settingsPtr) || !settingsPtr) return false;

  void *settingsClass = GetObjectClass(settingsPtr);
  void *targetField = FindFieldByName(settingsClass, settingName);
  if (!targetField)
    return false;

  size_t targetOffset = il2cpp_field_get_offset(targetField);
  uintptr_t settingParamPtr = 0;
  if (!SafeRead(settingsPtr + targetOffset, &settingParamPtr) || !settingParamPtr) return false;

  void *paramClass = GetObjectClass(settingParamPtr);
  void *paramValueField = FindFieldByName(paramClass, "paramValue");
  if (!paramValueField) return false;

  size_t paramOffset = il2cpp_field_get_offset(paramValueField);
  uintptr_t valueAddr = settingParamPtr + paramOffset;

  float oldValue = 0;
  SafeRead(valueAddr, &oldValue);

  if (writeInfo) {
    writeInfo->ownerPtr = settingsPtr;
    writeInfo->settingParamPtr = settingParamPtr;
    writeInfo->valueAddr = valueAddr;
    writeInfo->targetOffset = targetOffset;
    writeInfo->valueOffset = paramOffset;
    writeInfo->oldValue = oldValue;
    writeInfo->newValue = value;
    writeInfo->changed = FloatChanged(oldValue, value);
  }

  if (!SafeWrite(valueAddr, value)) return false;

  return true;
}

bool ApplyAnisotropicFiltering(int level, AnisoWriteInfo *writeInfo = nullptr) {
  if (writeInfo) {
    *writeInfo = {};
    writeInfo->level = level;
  }

  if (!il2cpp_class_from_name || !il2cpp_class_get_method_from_name)
    return false;

  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage) return false;

  Il2CppClass textureClass = il2cpp_class_from_name(coreImage, "UnityEngine", "Texture");
  if (!textureClass)
    return false;

  Il2CppMethodInfo setLimitsMethod = il2cpp_class_get_method_from_name(
      textureClass, "SetGlobalAnisotropicFilteringLimits", 2);
  if (setLimitsMethod) {
    void *methodPtr = GetMethodPointer(setLimitsMethod);
    if (methodPtr) {
      if (writeInfo) {
        writeInfo->methodPtr = methodPtr;
        writeInfo->methodName =
            "UnityEngine.Texture.SetGlobalAnisotropicFilteringLimits";
      }
      typedef void (*SetLimitsFunc)(int, int);
      ((SetLimitsFunc)methodPtr)(level, level);
      return true;
    }
  }

  Il2CppClass qualityClass = il2cpp_class_from_name(coreImage, "UnityEngine", "QualitySettings");
  if (qualityClass) {
    Il2CppMethodInfo setAniso = il2cpp_class_get_method_from_name(
        qualityClass, "set_anisotropicFiltering", 1);
    if (setAniso) {
      void *methodPtr = GetMethodPointer(setAniso);
      if (methodPtr) {
        if (writeInfo) {
          writeInfo->methodPtr = methodPtr;
          writeInfo->methodName =
              "UnityEngine.QualitySettings.set_anisotropicFiltering";
        }
        int mode = (level > 1) ? 2 : (level > 0 ? 1 : 0);
        typedef void (*SetAnisoFunc)(int);
        ((SetAnisoFunc)methodPtr)(mode);
      }
    }
  }

  return true;
}

bool ApplyGraphicsSettings(const GfxConfigSnapshot *before = nullptr) {
  bool success = true;

  int ssrEnable = -1;
  int ssrSamples = -1;
  int ssrUpsample = -1;
  ResolveSSRValues(g_ssrQuality, g_ssrEnable, g_ssrSampleCount,
                   g_ssrUpsampling, &ssrEnable, &ssrSamples, &ssrUpsample);
  if (g_ssrQuality == 4)
    g_ssrResScale = 1.0f;

  int oldSsrEnable = -1;
  int oldSsrSamples = -1;
  int oldSsrUpsample = -1;
  if (before) {
    ResolveSSRValues(before->ssrQuality, before->ssrEnable,
                     before->ssrSampleCount, before->ssrUpsampling,
                     &oldSsrEnable, &oldSsrSamples, &oldSsrUpsample);
  }

#define APPLY_GRAPHICS_INT(configName, il2cppField, runtimeField, value, oldValue) \
  do { \
    bool active = (value) >= 0; \
    bool oldActive = before ? (oldValue) >= 0 : false; \
    bool logThis = ShouldLogIntApply((value), (oldValue), active, oldActive, before); \
    if (active) { \
      IntWriteInfo info; \
      bool ok = SetSettingParameterValue((runtimeField), (value), &info); \
      success &= ok; \
      if (logThis) \
        LogIntWriteResult((configName), (il2cppField), ok, info); \
    } else if (logThis) { \
      LogSettingDisabled((configName)); \
    } \
  } while (0)

  APPLY_GRAPHICS_INT("SSREnable",
                     "HGSettingParameters.ssrEnable.paramValue",
                     "ssrEnable", ssrEnable, oldSsrEnable);
  APPLY_GRAPHICS_INT("SSRSampleCount",
                     "HGSettingParameters.ssrRayMarchingSampleCount.paramValue",
                     "ssrRayMarchingSampleCount", ssrSamples, oldSsrSamples);
  APPLY_GRAPHICS_INT("SSRUpsampling",
                     "HGSettingParameters.ssrV2Upsample.paramValue",
                     "ssrV2Upsample", ssrUpsample, oldSsrUpsample);

#undef APPLY_GRAPHICS_INT

  bool anisoActive = g_anisoLevel > 0;
  bool oldAnisoActive = before ? before->anisoLevel > 0 : false;
  int oldAnisoValue = before ? before->anisoLevel : -1;
  bool logAniso = ShouldLogIntApply(g_anisoLevel, oldAnisoValue, anisoActive,
                                    oldAnisoActive, before);
  if (anisoActive) {
    AnisoWriteInfo info;
    bool ok = ApplyAnisotropicFiltering(g_anisoLevel, &info);
    success &= ok;
    if (logAniso)
      LogAnisoWriteResult(ok, info);
  } else if (logAniso) {
    LogSettingDisabled("AnisoLevel");
  }

#define APPLY_SHARPEN_FLOAT(configName, il2cppField, runtimeField) \
  do { \
    bool active = g_sharpening >= 0.0f; \
    bool oldActive = before ? before->sharpening >= 0.0f : false; \
    float oldValue = before ? before->sharpening : -1.0f; \
    bool logThis = ShouldLogFloatApply(g_sharpening, oldValue, active, oldActive, before); \
    if (active) { \
      FloatWriteInfo info; \
      bool ok = SetSettingParameterFloatValue((runtimeField), g_sharpening, &info); \
      success &= ok; \
      if (logThis) \
        LogFloatWriteResult((configName), (il2cppField), ok, info); \
    } else if (logThis) { \
      LogSettingDisabled((configName)); \
    } \
  } while (0)

  APPLY_SHARPEN_FLOAT("Sharpening 1K",
                      "HGSettingParameters.sharpenStrength1K.paramValue",
                      "sharpenStrength1K");
  APPLY_SHARPEN_FLOAT("Sharpening 2K",
                      "HGSettingParameters.sharpenStrength2K.paramValue",
                      "sharpenStrength2K");
  APPLY_SHARPEN_FLOAT("Sharpening 4K",
                      "HGSettingParameters.sharpenStrength4K.paramValue",
                      "sharpenStrength4K");

#undef APPLY_SHARPEN_FLOAT

  return success;
}

static int g_lastAppliedAAMode = -99;
static int g_lastAppliedSMAAQuality = -99;
static bool g_aaFieldOffsetCached = false;
static uint32_t g_aaFieldOffset = 0;

bool ApplyAAToAllCameras(int aaMode, CameraAAWriteInfo *writeInfo = nullptr) {
  if (writeInfo) {
    *writeInfo = {};
    writeInfo->newValue = aaMode;
  }

  if (!il2cpp_class_from_name || !il2cpp_class_get_fields || !il2cpp_field_get_name ||
      !il2cpp_field_get_offset || !il2cpp_class_get_type || !il2cpp_type_get_object ||
      !il2cpp_runtime_invoke || !il2cpp_class_get_method_from_name)
    return false;

  Il2CppImage hgRenderImage = FindImage("HG.RenderPipelines.Runtime");
  if (!hgRenderImage)
    return false;

  Il2CppClass camDataClass = il2cpp_class_from_name(
      hgRenderImage, "HG.Rendering.Runtime", "HGAdditionalCameraData");
  if (!camDataClass)
    return false;

  if (!g_aaFieldOffsetCached) {
    void *iter = nullptr;
    while (void *field = il2cpp_class_get_fields(camDataClass, &iter)) {
      const char *name = il2cpp_field_get_name(field);
      if (name && strcmp(name, "antialiasing") == 0) {
        g_aaFieldOffset = (uint32_t)il2cpp_field_get_offset(field);
        g_aaFieldOffsetCached = true;
        break;
      }
    }
    if (!g_aaFieldOffsetCached)
      return false;
  }

  if (writeInfo)
    writeInfo->fieldOffset = g_aaFieldOffset;

  void *type = il2cpp_class_get_type(camDataClass);
  void *systemType = il2cpp_type_get_object(type);
  if (!systemType)
    return false;

  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage)
    return false;

  Il2CppClass unityObjectClass = il2cpp_class_from_name(coreImage, "UnityEngine", "Object");
  if (!unityObjectClass)
    return false;

  Il2CppMethodInfo findMethod = il2cpp_class_get_method_from_name(
      unityObjectClass, "FindObjectsOfType", 1);
  if (!findMethod)
    return false;

  void *args[1] = { systemType };
  void *exc = nullptr;
  void *result = il2cpp_runtime_invoke(findMethod, nullptr, args, &exc);

  if (exc)
    return false;

  if (!result)
    return true;

  uint32_t count = 0;
  SafeRead((uintptr_t)result + 0x18, &count);
  if (writeInfo)
    writeInfo->cameraCount = count;

  if (count == 0)
    return true;

  for (uint32_t i = 0; i < count; i++) {
    uintptr_t objAddr = 0;
    SafeRead((uintptr_t)result + 0x20 + (i * 8), &objAddr);
    if (objAddr) {
      int currentVal = 0;
      SafeRead(objAddr + g_aaFieldOffset, &currentVal);
      if (currentVal != aaMode) {
        if (writeInfo && writeInfo->changedCount == 0) {
          writeInfo->firstChangedCamera = objAddr;
          writeInfo->firstOldValue = currentVal;
        }
        if (writeInfo)
          writeInfo->changedCount++;
        SafeWrite(objAddr + g_aaFieldOffset, aaMode);
      }
    }
  }

  return true;
}

bool ApplySMAAQuality(int quality, SMAAWriteInfo *writeInfo = nullptr) {
  if (writeInfo) {
    *writeInfo = {};
    writeInfo->newValue = quality;
  }

  if (!il2cpp_class_from_name || !il2cpp_class_get_field_from_name ||
      !il2cpp_field_static_get_value || !il2cpp_field_get_offset)
    return false;

  Il2CppImage hgRenderImage = FindImage("HG.RenderPipelines.Runtime");
  if (!hgRenderImage)
    return false;

  Il2CppClass smaaClass = il2cpp_class_from_name(
      hgRenderImage, "HG.Rendering.Runtime", "HGSMAA");
  if (!smaaClass)
    return false;

  void *instanceField = il2cpp_class_get_field_from_name(smaaClass, "s_instance");
  if (!instanceField)
    return false;

  uintptr_t lazyPtr = 0;
  il2cpp_field_static_get_value(instanceField, &lazyPtr);
  if (!lazyPtr)
    return false;

  uintptr_t smaaInstance = 0;

  SafeRead(lazyPtr + 0x10, &smaaInstance);

  if (!smaaInstance)
    SafeRead(lazyPtr + 0x18, &smaaInstance);

  if (!smaaInstance) {
    Il2CppMethodInfo getInstanceMethod = il2cpp_class_get_method_from_name(smaaClass, "get_instance", 0);
    if (getInstanceMethod) {
      void *exc = nullptr;
      void *result = il2cpp_runtime_invoke(getInstanceMethod, nullptr, nullptr, &exc);
      if (exc)
        return false;
      if (result)
        smaaInstance = (uintptr_t)result;
    }

    if (!smaaInstance)
      return false;
  }

  const size_t SMAA_MODE_OFFSET = 0x10;

  int currentMode = 0;
  SafeRead(smaaInstance + SMAA_MODE_OFFSET, &currentMode);

  if (writeInfo) {
    writeInfo->smaaInstance = smaaInstance;
    writeInfo->valueAddr = smaaInstance + SMAA_MODE_OFFSET;
    writeInfo->valueOffset = SMAA_MODE_OFFSET;
    writeInfo->oldValue = currentMode;
    writeInfo->changed = currentMode != quality;
  }

  if (currentMode != quality && !SafeWrite(smaaInstance + SMAA_MODE_OFFSET, quality))
    return false;

  return true;
}

bool ApplyAASettings(const GfxConfigSnapshot *before = nullptr) {
  bool success = true;
  bool aaActive = g_aaMode == 0;
  bool oldAAActive = before ? before->aaMode == 0 : false;
  int oldAAValue = before ? before->aaMode : 1;
  bool logAA = ShouldLogIntApply(g_aaMode, oldAAValue, aaActive,
                                 oldAAActive, before);

  if (g_aaMode == 0) {
    CameraAAWriteInfo info;
    if (ApplyAAToAllCameras(0, &info)) {
      g_lastAppliedAAMode = 0;
      if (logAA)
        LogCameraAAWriteResult(true, info);
    } else {
      success = false;
      if (logAA)
        LogCameraAAWriteResult(false, info);
    }

    bool smaaActive = g_smaaQuality >= 0;
    bool oldSmaaActive = before ? before->smaaQuality >= 0 && oldAAActive : false;
    int oldSmaaValue = before ? before->smaaQuality : -1;
    bool logSmaa = ShouldLogIntApply(g_smaaQuality, oldSmaaValue,
                                     smaaActive, oldSmaaActive, before);
    if (g_smaaQuality >= 0) {
      SMAAWriteInfo smaaInfo;
      if (ApplySMAAQuality(g_smaaQuality, &smaaInfo)) {
        g_lastAppliedSMAAQuality = g_smaaQuality;
        if (logSmaa)
          LogSMAAWriteResult(true, smaaInfo);
      } else {
        success = false;
        if (logSmaa)
          LogSMAAWriteResult(false, smaaInfo);
      }
    } else if (logSmaa) {
      LogSettingDisabled("SMAA");
    }
  } else {
    g_lastAppliedAAMode = 1;
    if (logAA)
      LogSettingDisabled("AA");
  }

  return success;
}

float GetPrivateProfileFloat(const char *section, const char *key,
                             float defaultVal, const char *iniPath) {
  char buffer[64];
  GetPrivateProfileStringA(section, key, "", buffer, sizeof(buffer), iniPath);
  if (buffer[0] == '\0')
    return defaultVal;
  return (float)atof(buffer);
}

int GetPrivateProfileBool(const char *section, const char *key, int defaultVal,
                          const char *iniPath) {
  return GetPrivateProfileIntA(section, key, defaultVal, iniPath);
}

void UpdateIniPath() {
  char exePath[MAX_PATH];
  GetModuleFileNameA(NULL, exePath, MAX_PATH);
  std::string dir(exePath);
  size_t lastSlash = dir.rfind('\\');
  if (lastSlash != std::string::npos)
    dir = dir.substr(0, lastSlash + 1);
  std::string iniPath = dir + "EndfieldGFX.ini";
  strncpy(g_iniPath, iniPath.c_str(), MAX_PATH - 1);
  g_iniPath[MAX_PATH - 1] = '\0';
}

bool RefreshConfigLastWriteTime() {
  if (g_iniPath[0] == '\0')
    UpdateIniPath();

  WIN32_FILE_ATTRIBUTE_DATA data = {};
  if (!GetFileAttributesExA(g_iniPath, GetFileExInfoStandard, &data)) {
    g_configLastWriteTimeValid = false;
    return false;
  }

  g_configLastWriteTime = data.ftLastWriteTime;
  g_configLastWriteTimeValid = true;
  return true;
}

bool HasConfigChangedOnDisk() {
  if (g_iniPath[0] == '\0')
    UpdateIniPath();

  WIN32_FILE_ATTRIBUTE_DATA data = {};
  if (!GetFileAttributesExA(g_iniPath, GetFileExInfoStandard, &data))
    return false;

  if (!g_configLastWriteTimeValid)
    return true;

  return CompareFileTime(&data.ftLastWriteTime, &g_configLastWriteTime) != 0;
}

void LoadConfig() {
  UpdateIniPath();

  DWORD attrib = GetFileAttributesA(g_iniPath);
  if (attrib == INVALID_FILE_ATTRIBUTES)
    return;

  g_logging = GetPrivateProfileBool("Graphics", "Logging", 1, g_iniPath);
  g_liveEdit = GetPrivateProfileBool("Graphics", "LiveEdit", 0, g_iniPath);
  g_liveEditIntervalMs = GetPrivateProfileIntA(
      "Graphics", "LiveEditIntervalMs", DEFAULT_LIVE_EDIT_INTERVAL_MS,
      g_iniPath);
  if (g_liveEditIntervalMs < 250)
    g_liveEditIntervalMs = 250;
  if (g_liveEditIntervalMs > 10000)
    g_liveEditIntervalMs = 10000;

  g_gtaoScale = GetPrivateProfileFloat("Graphics", "GTAORes", -1.0f, g_iniPath);
  g_csmShadowSoftness = GetPrivateProfileFloat("Graphics", "CSMShadowSoftness", -1.0f, g_iniPath);

  g_csmShadowRes = GetPrivateProfileIntA("Graphics", "CSMShadowRes", -1, g_iniPath);
  g_charShadowRes = GetPrivateProfileIntA("Graphics", "CharacterShadowRes", -1, g_iniPath);
  g_punctualShadowRes = GetPrivateProfileIntA("Graphics", "PunctualLightShadowRes", -1, g_iniPath);
  g_asmShadowRes = GetPrivateProfileIntA("Graphics", "ASMShadowRes", -1, g_iniPath);

  g_screenSpaceShadowMask = GetPrivateProfileIntA("Graphics", "ScreenSpaceShadowMask", -1, g_iniPath);

  g_csmShadowSampleMode = GetPrivateProfileIntA("Graphics", "CSMShadowSampleMode", -1, g_iniPath);
  g_charShadowSampleMode = GetPrivateProfileIntA("Graphics", "CharacterShadowSampleMode", -1, g_iniPath);

  g_csmDepthBias = GetPrivateProfileFloat("Graphics", "CSMDepthBias", -1.0f, g_iniPath);
  g_csmNormalBias = GetPrivateProfileFloat("Graphics", "CSMNormalBias", -1.0f, g_iniPath);
  g_csmIntensity = GetPrivateProfileFloat("Graphics", "CSMIntensity", -1.0f, g_iniPath);

  g_contactShadowIntensity = GetPrivateProfileFloat("Graphics", "ContactShadowIntensity", -1.0f, g_iniPath);
  g_contactShadowThickness = GetPrivateProfileFloat("Graphics", "ContactShadowThickness", -1.0f, g_iniPath);
  g_contactShadowBilinear = GetPrivateProfileFloat("Graphics", "ContactShadowBilinear", -1.0f, g_iniPath);
  g_contactShadowContract = GetPrivateProfileFloat("Graphics", "ContactShadowContract", -1.0f, g_iniPath);

  g_aaMode = GetPrivateProfileIntA("Graphics", "AA", 1, g_iniPath);
  g_smaaQuality = GetPrivateProfileIntA("Graphics", "SMAA", -1, g_iniPath);
  if (g_smaaQuality < -1)
    g_smaaQuality = -g_smaaQuality;

  g_ssrQuality = GetPrivateProfileIntA("Graphics", "SSRQuality", -1, g_iniPath);
  g_ssrEnable = GetPrivateProfileIntA("Graphics", "SSREnable", -1, g_iniPath);
  g_ssrSampleCount = GetPrivateProfileIntA("Graphics", "SSRSampleCount", -1, g_iniPath);
  g_ssrUpsampling = GetPrivateProfileIntA("Graphics", "SSRUpsampling", -1, g_iniPath);

  g_renderScale = GetPrivateProfileFloat("Graphics", "RenderScale", -1.0f, g_iniPath);

  g_anisoLevel = GetPrivateProfileIntA("Graphics", "AnisoLevel", -1, g_iniPath);
  if (g_anisoLevel < -1)
    g_anisoLevel = -g_anisoLevel;

  g_sharpening = GetPrivateProfileFloat("Graphics", "Sharpening", -1.0f, g_iniPath);
}

void LogConfigSelection(const char *reason, const GfxConfigSnapshot *before) {
  Log("%s config:", reason);
  Log("  path: %s", g_iniPath);

  if (!before) {
    if (g_liveEdit || g_liveEditIntervalMs != DEFAULT_LIVE_EDIT_INTERVAL_MS) {
      Log("  controls:");
      Log("    LiveEdit = %d", g_liveEdit);
      Log("    LiveEditIntervalMs = %d", g_liveEditIntervalMs);
    }
  } else if (g_liveEdit != before->liveEdit ||
             g_liveEditIntervalMs != before->liveEditIntervalMs) {
    Log("  controls changed:");
    if (g_liveEdit != before->liveEdit)
      Log("    LiveEdit: %d -> %d", before->liveEdit, g_liveEdit);
    if (g_liveEditIntervalMs != before->liveEditIntervalMs)
      Log("    LiveEditIntervalMs: %d -> %d", before->liveEditIntervalMs,
          g_liveEditIntervalMs);
  }

  Log("  %s graphics edits:", before ? "changed" : "active");
  int logged = 0;

  LogConfigFloatSetting("GTAORes", g_gtaoScale,
                        before ? before->gtaoScale : -1.0f,
                        g_gtaoScale >= 0.0f,
                        before ? before->gtaoScale >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("CSMShadowSoftness", g_csmShadowSoftness,
                        before ? before->csmShadowSoftness : -1.0f,
                        g_csmShadowSoftness >= 0.0f,
                        before ? before->csmShadowSoftness >= 0.0f : false,
                        before, &logged);
  LogConfigIntSetting("CSMShadowRes", g_csmShadowRes,
                      before ? before->csmShadowRes : -1,
                      g_csmShadowRes >= 0,
                      before ? before->csmShadowRes >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("CharacterShadowRes", g_charShadowRes,
                      before ? before->charShadowRes : -1,
                      g_charShadowRes >= 0,
                      before ? before->charShadowRes >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("PunctualLightShadowRes", g_punctualShadowRes,
                      before ? before->punctualShadowRes : -1,
                      g_punctualShadowRes >= 0,
                      before ? before->punctualShadowRes >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("ASMShadowRes", g_asmShadowRes,
                      before ? before->asmShadowRes : -1,
                      g_asmShadowRes >= 0,
                      before ? before->asmShadowRes >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("CSMShadowSampleMode", g_csmShadowSampleMode,
                      before ? before->csmShadowSampleMode : -1,
                      g_csmShadowSampleMode >= 0,
                      before ? before->csmShadowSampleMode >= 0 : false,
                      before, &logged);
  LogConfigFloatSetting("CSMDepthBias", g_csmDepthBias,
                        before ? before->csmDepthBias : -1.0f,
                        g_csmDepthBias >= 0.0f,
                        before ? before->csmDepthBias >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("CSMNormalBias", g_csmNormalBias,
                        before ? before->csmNormalBias : -1.0f,
                        g_csmNormalBias >= 0.0f,
                        before ? before->csmNormalBias >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("CSMIntensity", g_csmIntensity,
                        before ? before->csmIntensity : -1.0f,
                        g_csmIntensity >= 0.0f,
                        before ? before->csmIntensity >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("ContactShadowIntensity", g_contactShadowIntensity,
                        before ? before->contactShadowIntensity : -1.0f,
                        g_contactShadowIntensity >= 0.0f,
                        before ? before->contactShadowIntensity >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("ContactShadowThickness", g_contactShadowThickness,
                        before ? before->contactShadowThickness : -1.0f,
                        g_contactShadowThickness >= 0.0f,
                        before ? before->contactShadowThickness >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("ContactShadowBilinear", g_contactShadowBilinear,
                        before ? before->contactShadowBilinear : -1.0f,
                        g_contactShadowBilinear >= 0.0f,
                        before ? before->contactShadowBilinear >= 0.0f : false,
                        before, &logged);
  LogConfigFloatSetting("ContactShadowContract", g_contactShadowContract,
                        before ? before->contactShadowContract : -1.0f,
                        g_contactShadowContract >= 0.0f,
                        before ? before->contactShadowContract >= 0.0f : false,
                        before, &logged);
  LogConfigIntSetting("AA", g_aaMode, before ? before->aaMode : 1,
                      g_aaMode == 0, before ? before->aaMode == 0 : false,
                      before, &logged);
  LogConfigIntSetting("SMAA", g_smaaQuality,
                      before ? before->smaaQuality : -1,
                      g_aaMode == 0 && g_smaaQuality >= 0,
                      before ? before->aaMode == 0 &&
                                   before->smaaQuality >= 0
                             : false,
                      before, &logged);
  LogConfigIntSetting("SSRQuality", g_ssrQuality,
                      before ? before->ssrQuality : -1,
                      g_ssrQuality >= 0,
                      before ? before->ssrQuality >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("SSREnable", g_ssrEnable,
                      before ? before->ssrEnable : -1,
                      g_ssrEnable >= 0,
                      before ? before->ssrEnable >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("SSRSampleCount", g_ssrSampleCount,
                      before ? before->ssrSampleCount : -1,
                      g_ssrSampleCount >= 0,
                      before ? before->ssrSampleCount >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("SSRUpsampling", g_ssrUpsampling,
                      before ? before->ssrUpsampling : -1,
                      g_ssrUpsampling >= 0,
                      before ? before->ssrUpsampling >= 0 : false,
                      before, &logged);
  LogConfigIntSetting("AnisoLevel", g_anisoLevel,
                      before ? before->anisoLevel : -1,
                      g_anisoLevel > 0,
                      before ? before->anisoLevel > 0 : false,
                      before, &logged);
  LogConfigFloatSetting("Sharpening", g_sharpening,
                        before ? before->sharpening : -1.0f,
                        g_sharpening >= 0.0f,
                        before ? before->sharpening >= 0.0f : false,
                        before, &logged);

  if (logged == 0)
    Log("    none");
}

bool ResolveIL2CppAPI() {
  g_hGameAssembly = GetModuleHandleW(L"GameAssembly.dll");
  if (!g_hGameAssembly)
    return false;
#define RESOLVE(name) name = (fn_##name)GetProcAddress(g_hGameAssembly, #name);
  RESOLVE(il2cpp_domain_get);
  RESOLVE(il2cpp_thread_attach);
  RESOLVE(il2cpp_domain_get_assemblies);
  RESOLVE(il2cpp_assembly_get_image);
  RESOLVE(il2cpp_image_get_name);
  RESOLVE(il2cpp_class_from_name);
  RESOLVE(il2cpp_class_get_method_from_name);
  RESOLVE(il2cpp_class_get_field_from_name);
  RESOLVE(il2cpp_field_static_get_value);
  RESOLVE(il2cpp_field_static_set_value);
  RESOLVE(il2cpp_field_get_value);
  RESOLVE(il2cpp_field_set_value);
  RESOLVE(il2cpp_field_get_offset);
  RESOLVE(il2cpp_class_get_fields);
  RESOLVE(il2cpp_field_get_name);
  RESOLVE(il2cpp_field_get_flags);
  RESOLVE(il2cpp_class_get_parent);
  RESOLVE(il2cpp_object_get_class);
  RESOLVE(il2cpp_class_get_type);
  RESOLVE(il2cpp_type_get_object);
  RESOLVE(il2cpp_runtime_invoke);
#undef RESOLVE
  return il2cpp_domain_get && il2cpp_class_from_name;
}

Il2CppImage FindImage(const char *name) {
  Il2CppDomain domain = il2cpp_domain_get();
  if (!domain)
    return nullptr;
  size_t count = 0;
  void **assemblies = il2cpp_domain_get_assemblies(domain, &count);
  if (!assemblies)
    return nullptr;
  for (size_t i = 0; i < count; i++) {
    Il2CppImage image = il2cpp_assembly_get_image(assemblies[i]);
    if (!image)
      continue;
    const char *n = il2cpp_image_get_name(image);
    if (n && strstr(n, name))
      return image;
  }
  return nullptr;
}

void *GetMethodPointer(Il2CppMethodInfo mi) {
  return mi ? ((MethodInfo *)mi)->methodPointer : nullptr;
}

int CallStaticIntGetter(Il2CppClass k, const char *m) {
  Il2CppMethodInfo mi = il2cpp_class_get_method_from_name(k, m, 0);
  if (!mi)
    return -1;
  void *p = GetMethodPointer(mi);
  return p ? ((int (*)())p)() : -1;
}

void GetScreenRes() {
  Il2CppImage coreImage = FindImage("UnityEngine.CoreModule");
  if (!coreImage)
    return;
  Il2CppClass screenClass =
      il2cpp_class_from_name(coreImage, "UnityEngine", "Screen");
  if (!screenClass)
    return;
  g_screenWidth = CallStaticIntGetter(screenClass, "get_width");
  g_screenHeight = CallStaticIntGetter(screenClass, "get_height");
}

bool ApplyUnityShadowSettings(int32_t targetRes) {
  static bool initialized = false;
  static void *settingParamsField = nullptr;
  static void *csmResField = nullptr;
  static void *charResField = nullptr;
  static void *paramValueField = nullptr;
  static Il2CppClass renderPipelineManagerClass = nullptr;
  static void *s_currentPipelineField = nullptr;

  if (!il2cpp_class_get_field_from_name || !il2cpp_field_static_get_value ||
      !il2cpp_field_get_value || !il2cpp_field_set_value) {
    return false;
  }

  if (!initialized) {
    Il2CppImage renderingImage = FindImage("UnityEngine.CoreModule");
    if (!renderingImage)
      return false;

    renderPipelineManagerClass = il2cpp_class_from_name(
        renderingImage, "UnityEngine.Rendering", "RenderPipelineManager");
    if (!renderPipelineManagerClass)
      return false;

    s_currentPipelineField = il2cpp_class_get_field_from_name(
        renderPipelineManagerClass, "s_currentPipeline");
    if (!s_currentPipelineField)
      return false;

    Il2CppImage hgRenderImage = FindImage("HG.RenderPipelines.Runtime");
    if (hgRenderImage) {
      Il2CppClass settingParamsClass = il2cpp_class_from_name(
          hgRenderImage, "HG.Rendering.Runtime", "HGSettingParameters");
      if (settingParamsClass) {
        csmResField = il2cpp_class_get_field_from_name(
            settingParamsClass, "<csmShadowMapTileResolution>k__BackingField");
        charResField = il2cpp_class_get_field_from_name(
            settingParamsClass,
            "<characterShadowMapResolution>k__BackingField");

        Il2CppClass settingParamIntClass = il2cpp_class_from_name(
            hgRenderImage, "HG.Rendering.Runtime", "SettingParameter`1");
        if (settingParamIntClass) {
          paramValueField = il2cpp_class_get_field_from_name(
              settingParamIntClass, "<paramValue>k__BackingField");
        }
      }
    }

    initialized = true;
  }

  if (!s_currentPipelineField)
    return false;

  void *currentPipeline = nullptr;
  il2cpp_field_static_get_value(s_currentPipelineField, &currentPipeline);
  if (!currentPipeline)
    return false;

  void *settingParams = nullptr;

  Il2CppMethodInfo getterMethod = il2cpp_class_get_method_from_name(
      *(Il2CppClass *)currentPipeline, "get_settingParameters", 0);
  if (getterMethod) {
    void *methodPtr = GetMethodPointer(getterMethod);
    if (methodPtr)
      settingParams = ((void *(*)(void *))methodPtr)(currentPipeline);
  }

  if (!settingParams) {
    void *field = il2cpp_class_get_field_from_name(
        *(Il2CppClass *)currentPipeline, "<settingParameters>k__BackingField");
    if (field)
      il2cpp_field_get_value(currentPipeline, field, &settingParams);
  }

  if (!settingParams)
    return false;

  if (csmResField && paramValueField) {
    void *csmSettingParam = nullptr;
    il2cpp_field_get_value(settingParams, csmResField, &csmSettingParam);
    if (csmSettingParam)
      il2cpp_field_set_value(csmSettingParam, paramValueField, &targetRes);
  }

  if (charResField && paramValueField) {
    void *charSettingParam = nullptr;
    il2cpp_field_get_value(settingParams, charResField, &charSettingParam);
    if (charSettingParam)
      il2cpp_field_set_value(charSettingParam, paramValueField, &targetRes);
  }

  return true;
}

typedef void (*RenderPathFunc_t)(int64_t _ptr, void *renderPathParams,
                                 void *beforeCullingParams, void *camera,
                                 void *renderContext, void *_cmd);
static RenderPathFunc_t g_OriginalRenderPath = nullptr;

void LogGTAOApplyResult(void *renderPathParams, void *gtaoPtr, int32_t oldWidth,
                        int32_t oldHeight, int32_t targetWidth,
                        int32_t targetHeight, bool wroteValues) {
  Log("GTAORes apply:");
  Log("  IL2CPP field: HGRenderPathParamsCPP.gtaoSettingParameters");
  Log("  renderPathParams: %p", renderPathParams);
  Log("  gtao settings pointer: %p", gtaoPtr);
  Log("  gtao offset: 0x%zX", g_renderHookOffsets.renderParamsGtaoPtr);
  Log("  width field offset: 0x%zX", g_renderHookOffsets.gtaoScreenWidth);
  Log("  height field offset: 0x%zX", g_renderHookOffsets.gtaoScreenHeight);
  Log("  screen resolution: %d x %d", g_screenWidth, g_screenHeight);
  if (g_gtaoOriginalWidth >= 0 && g_gtaoOriginalHeight >= 0)
    Log("  original GTAO resolution: %d x %d", g_gtaoOriginalWidth,
        g_gtaoOriginalHeight);
  if (g_gtaoPreviousWidth >= 0 && g_gtaoPreviousHeight >= 0)
    Log("  previous applied GTAO resolution: %d x %d", g_gtaoPreviousWidth,
        g_gtaoPreviousHeight);
  Log("  current GTAO resolution: %d x %d", oldWidth, oldHeight);
  Log("  target GTAO resolution: %d x %d", targetWidth, targetHeight);
  Log("  scale: %.3f", g_gtaoScale);
  Log("  value: %d x %d -> %d x %d (%s)", oldWidth, oldHeight, targetWidth,
      targetHeight, wroteValues ? "written" : "unchanged");
  Log("  result: OK");
}

void LogShadowConfigFloatResult(const char *settingName, const char *fieldName,
                                void *beforeCullingParams,
                                uintptr_t shadowConfigPtr, size_t fieldOffset,
                                float oldValue, float targetValue, bool ok,
                                bool wroteValue) {
  Log("%s apply:", settingName);
  Log("  IL2CPP field: HGShadowConfigCPP.%s", fieldName);
  Log("  beforeCullingParams: %p", beforeCullingParams);
  Log("  shadowConfig pointer: %p", (void *)shadowConfigPtr);
  Log("  field offset: 0x%zX", fieldOffset);
  Log("  value address: %p", (void *)(shadowConfigPtr + fieldOffset));
  if (ok)
    Log("  value: %.3f -> %.3f (%s)", oldValue, targetValue,
        wroteValue ? "written" : "unchanged");
  Log("  result: %s", ok ? "OK" : "FAILED");
}

void ApplyShadowConfigFloat(const char *settingName, const char *fieldName,
                            void *beforeCullingParams,
                            uintptr_t shadowConfigPtr, size_t fieldOffset,
                            float targetValue, float currentValue,
                            bool logResult) {
  bool changed = FloatChanged(currentValue, targetValue);
  bool ok = true;
  if (changed)
    ok = SafeWrite(shadowConfigPtr + fieldOffset, targetValue);
  if (logResult)
    LogShadowConfigFloatResult(settingName, fieldName, beforeCullingParams,
                               shadowConfigPtr, fieldOffset, currentValue,
                               targetValue, ok, changed && ok);
}

void HookedRenderPath(int64_t _ptr, void *renderPathParams,
                      void *beforeCullingParams, void *camera,
                      void *renderContext, void *_cmd) {
  if (renderPathParams) {
    __try {
      uint8_t *base = (uint8_t *)renderPathParams;

      if (g_gtaoScale >= 0) {
        void **gtaoPtrAddr =
            (void **)(base + g_renderHookOffsets.renderParamsGtaoPtr);
        void *gtaoPtr = *gtaoPtrAddr;

        if (gtaoPtr) {
          uint8_t *gtaoSettings = (uint8_t *)gtaoPtr;
          int32_t *pWidth =
              (int32_t *)(gtaoSettings + g_renderHookOffsets.gtaoScreenWidth);
          int32_t *pHeight =
              (int32_t *)(gtaoSettings + g_renderHookOffsets.gtaoScreenHeight);

          int32_t oldWidth = *pWidth;
          int32_t oldHeight = *pHeight;
          if (g_gtaoOriginalWidth < 0 || g_gtaoOriginalHeight < 0) {
            g_gtaoOriginalWidth = oldWidth;
            g_gtaoOriginalHeight = oldHeight;
          }

          int32_t targetW = (int32_t)(g_screenWidth * g_gtaoScale);
          int32_t targetH = (int32_t)(g_screenHeight * g_gtaoScale);
          bool changed = oldWidth != targetW || oldHeight != targetH;

          if (changed) {
            *pWidth = targetW;
            *pHeight = targetH;
            g_patchCount++;
            g_gtaoPatched = true;
          }

          if (g_logNextGTAOApply) {
            LogGTAOApplyResult(renderPathParams, gtaoPtr, oldWidth, oldHeight,
                               targetW, targetH, changed);
            g_logNextGTAOApply = false;
          }
          g_gtaoPreviousWidth = targetW;
          g_gtaoPreviousHeight = targetH;
        } else if (g_logNextGTAOApply) {
          Log("GTAORes apply:");
          Log("  IL2CPP field: HGRenderPathParamsCPP.gtaoSettingParameters");
          Log("  renderPathParams: %p", renderPathParams);
          Log("  gtao settings pointer: null");
          Log("  result: FAILED");
          g_logNextGTAOApply = false;
        }
      }

    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
  }

  if (beforeCullingParams) {
    __try {
      uintptr_t shadowConfigPtr = 0;
      if (!SafeRead((uintptr_t)beforeCullingParams +
                        g_renderHookOffsets.beforeCullingShadowConfigPtr,
                    &shadowConfigPtr)) {
        if (HasPendingShadowApplyLog()) {
          Log("HGShadowConfigCPP apply:");
          Log("  beforeCullingParams: %p", beforeCullingParams);
          Log("  shadowConfig offset: 0x%zX",
              g_renderHookOffsets.beforeCullingShadowConfigPtr);
          Log("  result: FAILED");
          ClearPendingShadowApplyLogs();
        }
        goto call_original;
      }
      if (!shadowConfigPtr) {
        if (HasPendingShadowApplyLog()) {
          Log("HGShadowConfigCPP apply:");
          Log("  beforeCullingParams: %p", beforeCullingParams);
          Log("  shadowConfig pointer: null");
          Log("  result: FAILED");
          ClearPendingShadowApplyLogs();
        }
        goto call_original;
      }

      float currentSoftness = 0.0f;
      if (!SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowCsmSoftness,
                    &currentSoftness)) {
        if (HasPendingShadowApplyLog()) {
          Log("HGShadowConfigCPP apply:");
          Log("  shadowConfig pointer: %p", (void *)shadowConfigPtr);
          Log("  first field read: csmShadowSoftness");
          Log("  result: FAILED");
          ClearPendingShadowApplyLogs();
        }
        goto call_original;
      }

      float curDepthBias = 0, curNormalBias = 0, curIntensity = 0;
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowCsmDepthBias,
               &curDepthBias);
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowCsmNormalBias,
               &curNormalBias);
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowCsmIntensity,
               &curIntensity);

      float contactIntensity = 0, contactThickness = 0, contactBilinear = 0, contactContract = 0;
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowContactIntensity,
               &contactIntensity);
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowContactThickness,
               &contactThickness);
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowContactBilinear,
               &contactBilinear);
      SafeRead(shadowConfigPtr + g_renderHookOffsets.shadowContactContract,
               &contactContract);

      bool logShadow = HasPendingShadowApplyLog();

      if (g_csmShadowSoftness >= 0)
        ApplyShadowConfigFloat("CSMShadowSoftness", "csmShadowSoftness",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowCsmSoftness,
                               g_csmShadowSoftness, currentSoftness,
                               g_logNextCsmShadowSoftnessApply);
      if (g_csmDepthBias >= 0)
        ApplyShadowConfigFloat("CSMDepthBias", "csmDepthBias",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowCsmDepthBias,
                               g_csmDepthBias, curDepthBias,
                               g_logNextCsmDepthBiasApply);
      if (g_csmNormalBias >= 0)
        ApplyShadowConfigFloat("CSMNormalBias", "csmNormalBias",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowCsmNormalBias,
                               g_csmNormalBias, curNormalBias,
                               g_logNextCsmNormalBiasApply);
      if (g_csmIntensity >= 0)
        ApplyShadowConfigFloat("CSMIntensity", "csmIntensity",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowCsmIntensity,
                               g_csmIntensity, curIntensity,
                               g_logNextCsmIntensityApply);

      if (g_contactShadowIntensity >= 0)
        ApplyShadowConfigFloat("ContactShadowIntensity",
                               "contactShadowIntensity", beforeCullingParams,
                               shadowConfigPtr,
                               g_renderHookOffsets.shadowContactIntensity,
                               g_contactShadowIntensity, contactIntensity,
                               g_logNextContactShadowIntensityApply);
      if (g_contactShadowThickness >= 0)
        ApplyShadowConfigFloat("ContactShadowThickness",
                               "contactShadowSurfaceThickness",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowContactThickness,
                               g_contactShadowThickness, contactThickness,
                               g_logNextContactShadowThicknessApply);
      if (g_contactShadowBilinear >= 0)
        ApplyShadowConfigFloat("ContactShadowBilinear",
                               "contactShadowBilinearThreshold",
                               beforeCullingParams, shadowConfigPtr,
                               g_renderHookOffsets.shadowContactBilinear,
                               g_contactShadowBilinear, contactBilinear,
                               g_logNextContactShadowBilinearApply);
      if (g_contactShadowContract >= 0)
        ApplyShadowConfigFloat("ContactShadowContract",
                               "contactShadowContract", beforeCullingParams,
                               shadowConfigPtr,
                               g_renderHookOffsets.shadowContactContract,
                               g_contactShadowContract, contactContract,
                               g_logNextContactShadowContractApply);

      if (logShadow)
        ClearPendingShadowApplyLogs();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
  }

call_original:

  if (g_TrampolineFunc) {
    ((RenderPathFunc_t)g_TrampolineFunc)(_ptr, renderPathParams,
                                         beforeCullingParams, camera,
                                         renderContext, _cmd);
  }
}

bool InstallHookWithTrampoline(void *target) {
  if (!target)
    return false;

  const int HOOK_SIZE = 16;

  memcpy(g_OriginalBytes, target, HOOK_SIZE);

  uintptr_t targetAddr = (uintptr_t)target;
  g_pTrampoline = nullptr;

  const uintptr_t MAX_RANGE = 0x7FFF0000;
  const uintptr_t STEP = 0x10000;

  for (uintptr_t offset = STEP; offset < MAX_RANGE; offset += STEP) {
    void *tryAddr = (void *)(targetAddr - offset);
    g_pTrampoline = VirtualAlloc(tryAddr, 64, MEM_COMMIT | MEM_RESERVE,
                                 PAGE_EXECUTE_READWRITE);
    if (g_pTrampoline)
      break;

    tryAddr = (void *)(targetAddr + offset);
    g_pTrampoline = VirtualAlloc(tryAddr, 64, MEM_COMMIT | MEM_RESERVE,
                                 PAGE_EXECUTE_READWRITE);
    if (g_pTrampoline)
      break;
  }

  if (!g_pTrampoline)
    return false;

  memcpy(g_pTrampoline, target, HOOK_SIZE);

  uint8_t *trampolineBytes = (uint8_t *)g_pTrampoline;
  if (trampolineBytes[7] == 0x80 && trampolineBytes[8] == 0x3D) {
    int32_t origDisp = *(int32_t *)(trampolineBytes + 9);
    uintptr_t originalTargetAddr = (uintptr_t)target + 14 + origDisp;
    int32_t newDisp =
        (int32_t)(originalTargetAddr - ((uintptr_t)g_pTrampoline + 14));
    *(int32_t *)(trampolineBytes + 9) = newDisp;
  }

  uint8_t *trampolineJump = (uint8_t *)g_pTrampoline + HOOK_SIZE;
  trampolineJump[0] = 0x48;
  trampolineJump[1] = 0xB8;
  uintptr_t returnAddr = (uintptr_t)target + HOOK_SIZE;
  memcpy(&trampolineJump[2], &returnAddr, 8);
  trampolineJump[10] = 0xFF;
  trampolineJump[11] = 0xE0;

  g_TrampolineFunc = (ConvertSettingParamsToCpp_t)g_pTrampoline;

  DWORD oldProtect;
  if (!VirtualProtect(target, HOOK_SIZE, PAGE_EXECUTE_READWRITE, &oldProtect)) {
    VirtualFree(g_pTrampoline, 0, MEM_RELEASE);
    return false;
  }

  uint8_t hookCode[16] = {
      0x48, 0xB8, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00,
      0xFF, 0xE0,
      0x90, 0x90, 0x90, 0x90
  };
  uintptr_t hookAddr = (uintptr_t)&HookedRenderPath;
  memcpy(&hookCode[2], &hookAddr, 8);

  memcpy(target, hookCode, HOOK_SIZE);

  VirtualProtect(target, HOOK_SIZE, oldProtect, &oldProtect);

  FlushInstructionCache(GetCurrentProcess(), target, HOOK_SIZE);
  FlushInstructionCache(GetCurrentProcess(), g_pTrampoline, 64);

  g_HookInstalled = true;

  return true;
}

bool TryDirectPatch() {
  if (!ResolveRenderHookOffsets()) {
    Log("HGRenderPath_Render hook: skipped because metadata offsets failed");
    return false;
  }

  Il2CppImage graphicsImage = FindImage("UnityEngine.HGGraphicsCPPModule");
  if (!graphicsImage) {
    Log("HGRenderPath_Render hook: graphics image not found");
    return false;
  }

  Il2CppClass renderGraphClass = il2cpp_class_from_name(
      graphicsImage, "UnityEngine.HyperGryphEngineCode", "HGRenderGraphCPP");
  if (!renderGraphClass)
    renderGraphClass = il2cpp_class_from_name(graphicsImage, "", "HGRenderGraphCPP");

  if (renderGraphClass) {
    Il2CppMethodInfo renderMethod = il2cpp_class_get_method_from_name(
        renderGraphClass, "HGRenderPath_Render", 6);
    if (renderMethod) {
      g_ConvertMethodPtr = GetMethodPointer(renderMethod);
      if (g_ConvertMethodPtr) {
        bool installed = InstallHookWithTrampoline(g_ConvertMethodPtr);
        Log("HGRenderPath_Render hook: %s at %p",
            installed ? "installed" : "failed", g_ConvertMethodPtr);
        return installed;
      }
    }
  }

  Log("HGRenderPath_Render hook: method not found");
  return false;
}

void ApplyEnhancements() {
  LoadConfig();
  RefreshConfigLastWriteTime();
  GetScreenRes();
  LogConfigSelection("Startup", nullptr);
  Log("Screen resolution: %d x %d", g_screenWidth, g_screenHeight);
  bool renderHookOk = TryDirectPatch();
  Log("ApplyEnhancements: renderHook=%s", renderHookOk ? "OK" : "FAILED");
}

bool ApplyConfigBackedSettings(const GfxConfigSnapshot *before = nullptr,
                               const char *reason = "startup") {
  bool allSuccess = true;

  bool gtaoActive = g_gtaoScale >= 0.0f;
  bool oldGtaoActive = before ? before->gtaoScale >= 0.0f : false;
  bool logGtao = ShouldLogFloatApply(g_gtaoScale,
                                     before ? before->gtaoScale : -1.0f,
                                     gtaoActive, oldGtaoActive, before);
  if (gtaoActive && logGtao)
    g_logNextGTAOApply = true;
  else if (!gtaoActive && logGtao)
    LogSettingDisabled("GTAORes");

#define QUEUE_RENDER_FLOAT(configValue, beforeMember, configName, logFlag) \
  do { \
    bool active = (configValue) >= 0.0f; \
    bool oldActive = before ? before->beforeMember >= 0.0f : false; \
    bool logThis = ShouldLogFloatApply((configValue), \
                                       before ? before->beforeMember : -1.0f, \
                                       active, oldActive, before); \
    if (active && logThis) { \
      (logFlag) = true; \
    } else if (!active && logThis) { \
      (logFlag) = false; \
      LogSettingDisabled((configName)); \
    } \
  } while (0)

  QUEUE_RENDER_FLOAT(g_csmShadowSoftness, csmShadowSoftness,
                     "CSMShadowSoftness",
                     g_logNextCsmShadowSoftnessApply);
  QUEUE_RENDER_FLOAT(g_csmDepthBias, csmDepthBias, "CSMDepthBias",
                     g_logNextCsmDepthBiasApply);
  QUEUE_RENDER_FLOAT(g_csmNormalBias, csmNormalBias, "CSMNormalBias",
                     g_logNextCsmNormalBiasApply);
  QUEUE_RENDER_FLOAT(g_csmIntensity, csmIntensity, "CSMIntensity",
                     g_logNextCsmIntensityApply);
  QUEUE_RENDER_FLOAT(g_contactShadowIntensity, contactShadowIntensity,
                     "ContactShadowIntensity",
                     g_logNextContactShadowIntensityApply);
  QUEUE_RENDER_FLOAT(g_contactShadowThickness, contactShadowThickness,
                     "ContactShadowThickness",
                     g_logNextContactShadowThicknessApply);
  QUEUE_RENDER_FLOAT(g_contactShadowBilinear, contactShadowBilinear,
                     "ContactShadowBilinear",
                     g_logNextContactShadowBilinearApply);
  QUEUE_RENDER_FLOAT(g_contactShadowContract, contactShadowContract,
                     "ContactShadowContract",
                     g_logNextContactShadowContractApply);

#undef QUEUE_RENDER_FLOAT

  bool shadowOk = ApplyManagedShadowSettings(before);
  if (shadowOk)
    g_shadowPatched = true;
  else
    allSuccess = false;

  bool graphicsOk = ApplyGraphicsSettings(before);
  bool aaOk = ApplyAASettings(before);
  allSuccess &= graphicsOk && aaOk;

  Log("Apply summary:");
  Log("  reason: %s", reason);
  Log("  shadows: %s", shadowOk ? "OK" : "FAILED");
  Log("  graphics: %s", graphicsOk ? "OK" : "FAILED");
  Log("  aa: %s", aaOk ? "OK" : "FAILED");
  Log("  overall: %s", allSuccess ? "OK" : "FAILED");

  return allSuccess;
}

DWORD WINAPI EnforcerThread(LPVOID) {
  Il2CppDomain domain = il2cpp_domain_get();
  if (domain && il2cpp_thread_attach)
    il2cpp_thread_attach(domain);

  static bool initialSettingsApplied = false;
  DWORD lastLiveEditPollTick = GetTickCount();
  int tick = 0;

  while (true) {
    Sleep(APPLY_INTERVAL_MS);
    if (!g_initialized)
      continue;

    tick++;

    if (!initialSettingsApplied && tick >= 6) {
      if (ApplyConfigBackedSettings(nullptr, "startup"))
        initialSettingsApplied = true;
    }

    if (g_liveEdit) {
      DWORD now = GetTickCount();
      if ((DWORD)(now - lastLiveEditPollTick) >=
          (DWORD)g_liveEditIntervalMs) {
        lastLiveEditPollTick = now;
        if (HasConfigChangedOnDisk()) {
          GfxConfigSnapshot before = CaptureConfigSnapshot();
          Log("Live edit: detected EndfieldGFX.ini change");
          LoadConfig();
          LogConfigSelection("Live edit", &before);
          RefreshConfigLastWriteTime();
          if (ApplyConfigBackedSettings(&before, "live-edit"))
            initialSettingsApplied = true;
        }
      }
    }

    if (initialSettingsApplied && g_aaMode == 0) {
      ApplyAAToAllCameras(0);
      if (g_smaaQuality >= 0)
        ApplySMAAQuality(g_smaaQuality);
    }

    if (tick % 12 == 0)
      GetScreenRes();
  }
  return 0;
}

DWORD WINAPI InitThread(LPVOID) {
  HANDLE hMutex = CreateMutexA(NULL, TRUE, "Local\\Ace_GFX_Mutex");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    if (hMutex)
      CloseHandle(hMutex);
    return 0;
  }

  LoadConfig();
  ResetLogFile();
  Log("Ace_GFX loaded");
  Log("Executable: %s", GetExecutablePath().c_str());
  Log("Module: %s", GetSelfModulePath().c_str());

  Sleep(INIT_DELAY_MS);

  if (!ResolveIL2CppAPI()) {
    Log("ResolveIL2CppAPI failed");
    return 1;
  }
  Log("ResolveIL2CppAPI: OK");

  Il2CppDomain domain = il2cpp_domain_get();
  if (!domain) {
    Log("il2cpp_domain_get failed");
    return 1;
  }

  if (il2cpp_thread_attach)
    il2cpp_thread_attach(domain);

  Sleep(2000);

  g_initialized = true;
  ApplyEnhancements();

  CreateThread(NULL, 0, EnforcerThread, NULL, 0, NULL);
  Log("Enforcer thread created");

  return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
  if (reason == DLL_PROCESS_ATTACH) {
    g_hSelfModule = hModule;
    DisableThreadLibraryCalls(hModule);
    CreateThread(NULL, 0, InitThread, NULL, 0, NULL);
  } else if (reason == DLL_PROCESS_DETACH) {
    if (g_pTrampoline)
      VirtualFree(g_pTrampoline, 0, MEM_RELEASE);
  }
  return TRUE;
}
