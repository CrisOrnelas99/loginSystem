# Authentication System (C++)

Terminal-based authentication project using a service-oriented C++ architecture.

## Architecture Skeleton

The system is organized around `MasterService` as the runtime coordinator.

- `MasterService` (`loginSystem.cpp`)
  - Owns core services and UI modules.
  - Controls startup, login flow, role routing, logout, and shutdown.

- `UserData` (`UserData.hpp`)
  - Core user entity with id, username, password hash, MFA key, and role.

- `DatabaseService` (`Services/DatabaseService.hpp`)
  - Hash table with linked-list chaining.
  - `appendUser`, `search`, and `deleteUser` are already implemented.

- `AUTH` services (`Services/AUTH/`)
  - `AuthenticationService.hpp`: auth workflow interface.
  - `AuthorizationService.hpp`: role/permission interface.
  - `PasswordService.hpp`: hashing/password policy interface.
  - `ValidationService.hpp`: user input validation layer.

- Supporting services (`Services/`)
  - `AuditLogService.hpp`: security/event logging interface.
  - `ConfigService.hpp`: runtime config and `.env` policy interface.

- UI layer (`Services/UI/`)
  - `UIService.hpp`: shared UI contract (abstract interface).
  - `AdminUI.hpp`, `EmployeeUI.hpp`, `GuestUI.hpp`: role-specific UI declarations.

## Runtime Workflow

1. App starts, `MasterService` runs.
2. Terminal shows login/exit options.
3. User submits username/password/MFA.
4. Input is validated.
5. Authentication succeeds or fails.
6. On success, user enters role menu flow.
7. Role actions run with authorization checks.
8. Events are logged and policy values come from config.
9. User logs out or exits.
10. App shuts down cleanly.

## Current State

- Designed for interface-first implementation.
- Methods are intentionally left undefined in most services.
- Implemented areas:
  - `DatabaseService` methods
  - `ValidationService` input methods
- Remaining service/UI methods are declared and ready for implementation.

## Directory Layout

```text
loginSystem/
  loginSystem.cpp
  UserData.hpp
  CMakeLists.txt
  Services/
    DatabaseService.hpp
    AuditLogService.hpp
    ConfigService.hpp
    AUTH/
      AuthenticationService.hpp
      AuthorizationService.hpp
      PasswordService.hpp
      ValidationService.hpp
    UI/
      UIService.hpp
      AdminUI.hpp
      EmployeeUI.hpp
      GuestUI.hpp
```

## Build

```bash
g++ -std=c++17 loginSystem.cpp -o loginSystem
```
