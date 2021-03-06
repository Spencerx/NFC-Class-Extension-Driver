/*++

Copyright (c) Microsoft Corporation.  All Rights Reserved

Module Name:

    device.h

Abstract:

    Cx Device declarations.
    
Environment:

    User-mode Driver Framework

--*/

#pragma once

//
// The device extension for the Nfc Class extension
//
typedef struct _NFCCX_FDO_CONTEXT {

    WDFDEVICE Device;

    //
    // Pointer to the class extension client context
    //
    PNFCCX_CLIENT_GLOBALS NfcCxClientGlobal;

    //
    // State
    //
    _Guarded_by_(HasFailedWaitLock)
    BOOLEAN HasFailed;
    WDFWAITLOCK HasFailedWaitLock;

    //
    // Power State
    //
    BOOLEAN NfpRadioInterfaceCreated;
    BOOLEAN NfpPowerOffSystemOverride;  // TRUE == Nfp system state override is off
    BOOLEAN NfpPowerOffPolicyOverride;  // TRUE == Nfp radio state is off

    BOOLEAN SERadioInterfaceCreated;
    BOOLEAN SEPowerOffSystemOverride;   // TRUE == SE system state override is off
    BOOLEAN SEPowerOffPolicyOverride;   // TRUE == SE radio state is off

    PNFCCX_POWER_MANAGER Power;

    //
    // Registry-provided config
    //
    BOOLEAN LogNciDataMessages;
    _Guarded_by_(HasFailedWaitLock)
    ULONG NumDriverRestarts;

    //
    // IO Queues
    //
    WDFQUEUE DefaultQueue;
    WDFQUEUE SelfQueue;

    //
    // RF interface
    //
    PNFCCX_RF_INTERFACE RFInterface;

    //
    // Tml interface
    //
    PNFCCX_TML_INTERFACE TmlInterface;

    //
    // Pub/Sub DDI
    //
    PNFP_INTERFACE NfpInterface;

    //
    // SE DDI
    //
    PNFCCX_SE_INTERFACE SEInterface;

    //
    // SmartCard DDI
    //
    PNFCCX_SC_INTERFACE SCInterface;

    //
    // DTA interface
    //
    PNFCCX_DTA_INTERFACE DTAInterface;

}  NFCCX_FDO_CONTEXT, *PNFCCX_FDO_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(NFCCX_FDO_CONTEXT, NfcCxFdoGetContext)

//
// Wdf callbacks
//
EVT_WDF_OBJECT_CONTEXT_CLEANUP NfcCxFdoContextCleanup;
EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL NfcCxEvtDefaultIoControl;
EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL NfcCxEvtSelfIoControl;

NTSTATUS
NfcCxFdoCreate(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

NTSTATUS
NfcCxFdoReadCxDriverRegistrySettings(
    _Out_ BOOLEAN* pLogNciDataMessages
    );

NTSTATUS
NfcCxFdoReadCxDeviceVolatileRegistrySettings(
    _In_ WDFDEVICE Device,
    _Out_ ULONG* pNumDriverRestarts
    );

NTSTATUS
NfcCxFdoWriteCxDeviceVolatileRegistrySettings(
    _In_ WDFDEVICE Device,
    _In_ ULONG* pNumDriverRestarts
    );

NTSTATUS
NfcCxFdoReadPersistedDeviceRegistrySettings(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

NTSTATUS
NfcCxFdoWritePersistedDeviceRegistrySettings(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

NTSTATUS
NfcCxFdoInitialize(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

NTSTATUS
NfcCxFdoDeInitialize(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

NTSTATUS
NfcCxFdoCleanup(
    _In_ PNFCCX_FDO_CONTEXT FdoContext
    );

