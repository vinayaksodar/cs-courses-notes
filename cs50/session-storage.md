# Session Storage

User sessions can be stored in several ways:

- **JWT (JSON Web Tokens)**

  - Easiest to implement.
  - No server-side storage needed; the token itself carries the session data.
  - **Downside**: Harder to invalidate across all devices (unless using a blacklist or rotation strategy).

- **File System**

  - Simple and fast (no database query needed).
  - **Downside**: Not ideal for horizontally scaled apps (multiple backend instances), since each server has its own file system.

- **Database**
  - Slightly slower because it requires database calls.
  - Most **robust**: good for scaling, persistent across multiple servers, easy session invalidation.
