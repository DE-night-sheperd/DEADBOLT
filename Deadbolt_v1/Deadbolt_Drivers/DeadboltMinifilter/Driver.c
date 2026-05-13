/*
    Deadbolt Endpoint Shield - File System Minifilter Driver
    Monitors file system operations
*/

#include <fltKernel.h>
#include <dontuse.h>
#include <ntstrsafe.h>

#define DEADBOLT_MINIFILTER_POOL_TAG 'tbmD'
#define DEADBOLT_MINIFILTER_MAX_NAME 260

PFLT_FILTER gFilterHandle = NULL;

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

NTSTATUS
DeadboltMinifilterUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
);

NTSTATUS
DeadboltMinifilterInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
);

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreCreate(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
);

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreWrite(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
);

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreSetInformation(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
);

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE,
      0,
      DeadboltMinifilterPreCreate,
      NULL },

    { IRP_MJ_WRITE,
      0,
      DeadboltMinifilterPreWrite,
      NULL },

    { IRP_MJ_SET_INFORMATION,
      0,
      DeadboltMinifilterPreSetInformation,
      NULL },

    { IRP_MJ_OPERATION_END }
};

CONST FLT_REGISTRATION FilterRegistration = {
    sizeof(FLT_REGISTRATION),
    FLT_REGISTRATION_VERSION,
    0,
    NULL,
    Callbacks,
    DeadboltMinifilterUnload,
    NULL,
    DeadboltMinifilterInstanceSetup,
    NULL,
    NULL,
    NULL,
    NULL
};

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    NTSTATUS status;

    KdPrint(("[DeadboltMinifilter] DriverEntry called\n"));

    status = FltRegisterFilter(DriverObject, &FilterRegistration, &gFilterHandle);
    if (!NT_SUCCESS(status)) {
        KdPrint(("[DeadboltMinifilter] FltRegisterFilter failed: 0x%X\n", status));
        return status;
    }

    status = FltStartFiltering(gFilterHandle);
    if (!NT_SUCCESS(status)) {
        KdPrint(("[DeadboltMinifilter] FltStartFiltering failed: 0x%X\n", status));
        FltUnregisterFilter(gFilterHandle);
        return status;
    }

    KdPrint(("[DeadboltMinifilter] DriverEntry succeeded\n"));
    return STATUS_SUCCESS;
}

NTSTATUS
DeadboltMinifilterUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    UNREFERENCED_PARAMETER(Flags);

    KdPrint(("[DeadboltMinifilter] Unload called\n"));

    if (gFilterHandle != NULL) {
        FltUnregisterFilter(gFilterHandle);
        gFilterHandle = NULL;
    }

    KdPrint(("[DeadboltMinifilter] Unload succeeded\n"));
    return STATUS_SUCCESS;
}

NTSTATUS
DeadboltMinifilterInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);

    KdPrint(("[DeadboltMinifilter] InstanceSetup called\n"));
    return STATUS_SUCCESS;
}

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreCreate(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
)
{
    NTSTATUS status;
    PFLT_FILE_NAME_INFORMATION fileNameInfo;
    WCHAR fileNameBuffer[DEADBOLT_MINIFILTER_MAX_NAME];

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    *CompletionContext = NULL;

    status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &fileNameInfo);
    if (NT_SUCCESS(status)) {
        RtlZeroMemory(fileNameBuffer, sizeof(fileNameBuffer));
        
        if (fileNameInfo->Name.Length < sizeof(fileNameBuffer)) {
            RtlCopyMemory(fileNameBuffer, fileNameInfo->Name.Buffer, fileNameInfo->Name.Length);
        }

        KdPrint(("[DeadboltMinifilter] FILE CREATE/OPEN: %wZ\n", &fileNameInfo->Name));
        
        FltReleaseFileNameInformation(fileNameInfo);
    }

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreWrite(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
)
{
    NTSTATUS status;
    PFLT_FILE_NAME_INFORMATION fileNameInfo;

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    *CompletionContext = NULL;

    status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &fileNameInfo);
    if (NT_SUCCESS(status)) {
        KdPrint(("[DeadboltMinifilter] FILE WRITE: %wZ, Bytes: %llu\n", 
                 &fileNameInfo->Name, 
                 Data->Iopb->Parameters.Write.Length));
        
        FltReleaseFileNameInformation(fileNameInfo);
    }

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}

FLT_PREOP_CALLBACK_STATUS
DeadboltMinifilterPreSetInformation(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
)
{
    NTSTATUS status;
    PFLT_FILE_NAME_INFORMATION fileNameInfo;

    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    *CompletionContext = NULL;

    if (Data->Iopb->Parameters.SetFileInformation.FileInformationClass == FileDispositionInformation ||
        Data->Iopb->Parameters.SetFileInformation.FileInformationClass == FileDispositionInformationEx) {
        
        status = FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &fileNameInfo);
        if (NT_SUCCESS(status)) {
            KdPrint(("[DeadboltMinifilter] FILE DELETE: %wZ\n", &fileNameInfo->Name));
            FltReleaseFileNameInformation(fileNameInfo);
        }
    }

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}
