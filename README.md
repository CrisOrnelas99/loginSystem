# Authentication System (C++)

Terminal-based authentication system written in C++ with a service-oriented design. This project models real-world auth concepts (password hashing, MFA, session management, token generation, role-based authorization, input validation, and audit logging) while keeping the codebase modular and easy to extend.

## Features

- Role-based users: **Admin / Employee / Guest**
- User records via `UserData` (id, username, password hash, MFA key, role)
- Session model via `Session` (session id, user id, timestamps, token hash)
- Database layer (`DatabaseService`) using a **hash table with linked-list chaining** for collisions
- Authentication flow (`AuthenticationService`): password + MFA checks, lockout handling, session/token creation
- Authorization (`AuthorizationService`): role/permission checks for protected actions
- Password utilities (`PasswordService`): hashing, salting/peppering, compare hash, forgot password flow (planned)
- Token utilities (`TokenService`): generates random session tokens and hashes them for storage
- Session management (`SessionService`): tracks session lifetime, expiration, and validation
- Validation (`ValidationService`): safe user input + username checks
- Audit logging (`AuditLogService`): security event tracking (login success/failure, lockouts, etc.)
- Config (`ConfigService`): centralized security settings (timeouts, max attempts, etc.)

## Tech Stack

- **Language:** C++
- **Concepts:** OOP, service-layer design, hashing/token/session concepts, hash table + linked list collision handling

## Project Structure (logical)

- `UserData` — user identity + credentials (password hash, MFA key, role)
- `Session` — session record with timestamps and token hash
- `DatabaseService` — in-memory database (hash table + linked list chaining)
- `AuthenticationService` — login flow orchestration (password/MFA/lockout/session)
- `AuthorizationService` — role/permission checks (RBAC)
- `PasswordService` — password hashing/verification + reset flows (planned)
- `TokenService` — secure token generation + hashing
- `SessionService` — session creation/validation/expiration
- `ValidationService` — input validation and sanitization helpers
- `AuditLogService` — audit/security event logger
- `ConfigService` — security policy configuration

## Setup

### Build (example)
```bash
g++ -std=c++17 main.cpp -o auth_system
