# Authentication System (C++)

Terminal-based authentication project in C++ using a service-oriented architecture.  
This README focuses on architecture and directory implementation only.

## Architecture

The project is organized around a central controller (`MasterService`) and a set of service modules.

- `MasterService` (in `loginSystem.cpp`): top-level orchestrator that coordinates application flow.
- `UserData`: core user entity (id, username, password hash, MFA key, role).
- `DatabaseService`: in-memory hash table with linked-list chaining for collisions.
- `AuthenticationService`: authentication workflow boundary (currently scaffolded).
- `AuthorizationService`: role/permission boundary (currently scaffolded).
- `PasswordService`: password utility boundary (currently scaffolded).
- `AuditLogService`: audit logging boundary (currently scaffolded).
- `ConfigService`: configuration/policy boundary (currently scaffolded).
- UI layer split by role (`AdminUI`, `EmployeeUI`, `GuestUI`) via a shared `UIService` base.

Current status:
- `DatabaseService` contains implemented insert/search/delete behavior.
- Other service headers are intentionally declared as stubs for incremental development.

## Directory Implementation

```text
loginSystem/
  loginSystem.cpp
  UserData.hpp
  CMakeLists.txt
  Services/
    DatabaseService.hpp
    AuthenticationService.hpp
    AuthorizationService.hpp
    PasswordService.hpp
    AuditLogService.hpp
    ConfigService.hpp
    UI/
      UIService.hpp
      AdminUI.hpp
      EmployeeUI.hpp
      GuestUI.hpp
```

### Folder Roles

- `loginSystem.cpp`
  - Entry point (`main`) and `MasterService`.
  - Includes service interfaces and UI headers.

- `UserData.hpp`
  - Shared user model and `Role` enum used across services.

- `Services/`
  - Core service boundaries for authentication system responsibilities.
  - `DatabaseService.hpp` includes hash table + linked-list node implementation.
  - Remaining service files are intentionally minimal interfaces/placeholders.

- `Services/UI/`
  - Presentation layer abstractions and role-specific UI class declarations.
  - Keeps UI concerns isolated from core service logic.
