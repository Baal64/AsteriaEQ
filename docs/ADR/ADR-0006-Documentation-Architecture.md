# ADR-0006 - Architecture Documentation Strategy

- **Status:** Accepted
- **Date:** 2026-08-05
- **Decider:** Alexandre Ba

---

## Context

Asteria EQ is a long-term engineering project combining software,
embedded systems, electronics and mechanics.

Its development spans multiple iterations over an extended period.

Without structured documentation, architectural decisions would gradually
become implicit and difficult to recover.

The project therefore requires documentation that evolves together with the
implementation.

---

## Decision

Architecture documentation is considered part of the project itself.

Documentation is maintained alongside the source code and follows the same
quality standards.

Major technical decisions are recorded as Architecture Decision Records (ADR).

Architecture documents describe the current system.

ADR documents describe why the system became what it is.

Both are maintained under version control.

---

## Consequences

### Positive

- Easier long-term maintenance.
- Architectural decisions remain traceable.
- New contributors can understand the project faster.
- Reduced knowledge loss.
- Better consistency between hardware and software.

### Negative

- Additional effort when introducing architectural changes.
- Documentation must evolve with the implementation.

---

## Alternatives Considered

### Documentation at the end of the project

Rejected.

Architecture would progressively become undocumented and difficult to
understand.

### Code only

Rejected.

Source code explains implementation.

It does not explain architectural decisions.

---

## Impact on Architecture

The project documentation becomes a first-class artifact.

Implementation and documentation evolve together.

Every significant architectural decision must be reflected in the appropriate
documentation before implementation is considered complete.

---

## Related Documents

- SoftwareArchitecture.md
- HardwareArchitecture.md
- Pinout.md
- All ADR documents

---

## Design Principles

Documentation is part of the architecture.

Architecture is part of the implementation.

Implementation is not complete until the documentation reflects it.
