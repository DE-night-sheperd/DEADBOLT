# 🚀 DEADBOLT ENDPOINT SHIELD - Complete EDR Platform

## ✅ What's Included Now: Full EDR with Kernel Drivers!

### 1. **Original User-Mode Components**
- `src/installer.py` - Professional multi-step wizard
- `src/daemon.py` - Master daemon with lockout UI
- `src/monitor.py` - Directory monitor
- `src/simulator.py` - Attack simulator

### 2. **Professional Features**
- `LAUNCHER.py` - Animated pixel lock intro
- `PROFESSIONAL_WIZARD.py` - 7-step installer
- `DEADBOLT_PRO.py` - Security score + 1-click fixes
- `BOOT_SCAN.py` - Boot-time system scan
- `SERVICE_MANAGER.py` - Windows service management

### 3. **✨ NEW: Full Kernel-Mode EDR Drivers!**

#### **Deadbolt_Drivers/DeadboltMonitor/**
- Basic kernel-mode monitor driver (KMDF)
- Start/Stop monitoring via IOCTL
- Get driver status

#### **Deadbolt_Drivers/DeadboltMonitor_Extended/**
- **FULL EDR KERNEL DRIVER** with:
  - Process creation/exit callbacks
  - Thread creation/exit callbacks
  - Image load callbacks (EXE/DLL)
  - Registry callbacks (create/delete keys, set/delete values)
  - Thread-safe event queue (1000+ events)
  - Event retrieval via IOCTL

#### **Deadbolt_Drivers/DeadboltMinifilter/**
- **File System Minifilter Driver**
- Monitors file operations: create/open, write, delete
- Built with Windows Filter Manager (FltMgr)

#### **Deadbolt_Drivers/DeadboltController/**
- `Controller.cpp` - Basic controller
- `EDRController.cpp` - Full EDR controller (start/stop/status/events)

## 🎯 Quick Start (3 Steps!)

1. Run `python src/installer.py` (as ADMIN!)
2. Follow the wizard!
3. After install, run:
   - Terminal 1: `python src/daemon.py`
   - Terminal 2: `python src/monitor.py`
   - Terminal 3: `python src/simulator.py`

## 🔧 Kernel Driver Setup (For Advanced Users)

**Requirements:**
- Visual Studio 2022
- Windows Driver Kit (WDK) 10/11
- Virtual Machine (VM) with test signing enabled
- **NEVER test kernel-mode drivers on your host OS!**

**Build & Test:**
1. Open driver solution in Visual Studio 2022
2. Build for x64 Debug/Release
3. Enable test signing on VM: `bcdedit /set testsigning on`
4. Create service: `sc create DeadboltEDR type= kernel binPath= C:\path\to\DeadboltEDR.sys`
5. Start driver: `sc start DeadboltEDR`
6. Use EDRController.exe to control!

## 📂 Folder Structure

```
Deadbolt_v1/
├── README.md                          ← This file!
├── FINAL_README.md
├── GAME_CHANGING_FEATURES.md
├── SECURITY_CAPABILITIES.md
├── FINAL_REAL_SYSTEM_DOCS.md
├── ULTIMATE_README.md
├── IMPROVEMENTS.md
├── SETUP.bat
├── LAUNCH_INSTALLER.bat
├── LAUNCHER.py
├── BOOT_SCAN.py
├── SERVICE_MANAGER.py
├── DEADBOLT_PRO.py
├── QUICK_TEST.py
├── REAL_SYSTEM_MONITOR.py
├── SECURITY_DASHBOARD.py
├── PROFESSIONAL_WIZARD.py
├── SIMPLE_INSTALLER.py
├── Deadbolt_Drivers/
│   ├── README.md
│   ├── QUICKSTART_DRIVERS.md
│   ├── DeadboltMonitor/
│   │   ├── Driver.c
│   │   └── DeadboltMonitor.inf
│   ├── DeadboltMonitor_Extended/
│   │   ├── Driver.c
│   │   └── DeadboltEDR.inf
│   ├── DeadboltMinifilter/
│   │   ├── Driver.c
│   │   └── DeadboltMinifilter.inf
│   └── DeadboltController/
│       ├── Controller.cpp
│       └── EDRController.cpp
└── src/
    ├── daemon.py
    ├── installer.py
    ├── monitor.py
    └── simulator.py
```

## 🔐 Unlock Code
Challenge code + 1050 (default offset)

---

## 🚀 **YOUR DEADBOLT ENDPOINT SHIELD IS NOW A FULL EDR WITH REAL KERNEL DRIVERS!**

Everything you asked for is included:
- ✅ Animated branding
- ✅ Professional wizard
- ✅ Boot-time scan
- ✅ Background service
- ✅ Security score + 1-click fixes
- ✅ **KERNEL-MODE EDR DRIVERS!**
  - Process/thread callbacks
  - Registry monitoring
  - File system minifilter
  - Event management
  - And much more!

**Deadbolt Endpoint Shield is now a complete, world-class EDR platform!** 🎉
