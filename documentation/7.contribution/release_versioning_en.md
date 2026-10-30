@page page_release_versioning_en RT-Thread Versioning Policy and Implementation Rules

# RT-Thread Versioning Policy and Implementation Rules

[中文](release_versioning_cn.md) | [Release Process](release_process_en.md)

| Item | Details |
| --- | --- |
| Document version | 1.0 |
| Date | 2026-10-27 |
| Scope | RT-Thread mainline release planning, release publication, and stable branch maintenance |
| Companion document | [Release Process](release_process_en.md) |

Release cadence: In principle, a `Z` release is published every month. A `Y` release is published every 3–6 months, depending on accumulated features and maintenance resources. `X` releases have no fixed schedule.

## 1. Version Number Format

Official releases use the following format:

```text
vX.Y.Z
```

Examples: `v6.0.0`, `v6.1.0`, and `v6.1.1`.

The version number must be consistent across source version macros, the Git tag, the release, and deliverable names:

| Item | Example |
| --- | --- |
| Git tag | `v6.1.0` |
| `RT_VERSION_MAJOR` | `6` |
| `RT_VERSION_MINOR` | `1` |
| `RT_VERSION_PATCH` | `0` |

Routine commits do not increment the official version number. Development snapshots must be identified by the target version, full Git SHA, and build records, and must not be labeled as published official releases.

## 2. Version Components

| Component | Purpose | Typical RT-Thread changes |
| --- | --- | --- |
| `X`: major | Major features or an overhaul of the overall technical architecture | A new kernel, reworked core kernel mechanisms, a new device or driver framework, system architecture changes, coordinated upgrades across core subsystems, or major API/ABI or configuration changes requiring user migration |
| `Y`: minor | Feature extensions to the existing kernel and frameworks; released every 3–6 months, depending on accumulated features and resources | New kernel or component APIs, driver framework capabilities, file system or networking capabilities, architecture or chip family support, or a set of BSP or component features that forms a complete deliverable |
| `Z`: patch | Focused fixes, support, and local improvements; in principle, released every month | Bug and security fixes, local feature improvements, performance or resource optimizations, individual BSP adaptations, build fixes, and documentation fixes |

### 2.1 `X`: Major Version

An increment of `X` requires a comprehensive review and decision for changes such as:

- Introducing a new kernel or replacing core kernel mechanisms.
- Introducing a new device model, driver framework, or system-level software framework.
- Coordinating upgrades across multiple core subsystems that change how the system is used as a whole.
- Removing, renaming, or changing public APIs, the ABI, structure layouts, or system call conventions.
- Changing Kconfig, configuration formats, startup sequences, or data formats so that existing projects require migration.
- Delivering a major upgrade in overall capabilities and architecture, even if some APIs remain compatible.

Related supporting features must be included in the same major release plan.

### 2.2 `Y`: Minor Version

Increment `Y` for changes that meet the following conditions:

- Adding kernel APIs, component APIs, or reusable public capabilities while preserving compatibility with existing interfaces.
- Adding capabilities to driver frameworks, file systems, network stacks, or package frameworks.
- Adding support for an architecture, chip family, or group of BSPs that forms an independently deliverable platform capability.
- Completing several related small features that meet the release goals and form a complete, verifiable, releasable feature set.

An isolated feature, local parameter extension, or optimization of a single implementation does not automatically trigger a `Y` increment. Features must meet the delivery scope defined by the release milestone and have corresponding test evidence. The `Y` release cycle is 3–6 months; once selected, the specific cycle must be stated in the release goals. Features that cannot complete validation within that cycle must be deferred to the next release.

### 2.3 `Z`: Patch Version

Increment `Z` for changes that meet the following conditions:

- Fixing deadlocks, out-of-bounds access, memory leaks, boot failures, security vulnerabilities, build failures, or performance regressions.
- Improving local functionality, error handling, logging, performance, or resource usage.
- Adding an adaptation for an individual BSP, chip, or platform.
- Fixing documentation, tests, build scripts, or release materials.

A `Z` release must not introduce new public APIs, complete components, driver frameworks, architectural frameworks, or planned incompatible changes. If an individual BSP introduces a new driver framework, device model, or public API, the change requires a `Y` or `X` increment.

## 3. Version Classification Priority

When a release contains multiple types of changes, use the highest impact level to determine its version number:

```text
X: major > Y: minor > Z: patch
```

| Combination of changes | Classification |
| --- | --- |
| Major kernel/framework changes + new components + bug fixes | `X` |
| New component/API/platform capabilities + local fixes | `Y` |
| Bug fixes + individual BSP adaptations + performance optimizations | `Z` |
| Documentation, tests, CI, or release materials only | No official version increment |

Do not determine version numbers by commit count, PR count, lines of code, or development cycle length. Use feature boundaries, user impact, architectural impact, and completeness of delivery.

## 4. Implementation Rules by Version Component

**Basis for release: periodic evaluation + accumulated features.**

Developers are advised to use `X/Y` releases. `Z` releases serve as intermediate stabilization points for traceability.

### 4.1 `X` Releases

To be discussed.

### 4.2 `Y` Releases

| Item | Requirement |
| --- | --- |
| Maintenance approach | Manual work + CI, with staffing focused on BSP and driver maintenance |
| Main purpose | Stabilize and release major driver framework and kernel API changes, as well as support for new architectures and frameworks |
| Release frequency | A 3–6 month cycle, with core maintainers reviewing and deciding whether to release |

**Release strategy:**

1. CI provides a test checklist and firmware for the corresponding test cases.
2. Testers perform manual validation and upload the results.
3. AI uses prompts or skills to consolidate the results into a release test report.
4. Humans review the report, and core maintainers decide whether to release based on accumulated features and validation results.

### 4.3 `Z` Releases

**Prerequisite: the mainline has an initial, reasonably complete automated workflow in place.**

| Item | Requirement |
| --- | --- |
| Maintenance approach | Primarily QEMU + CI automation |
| Test scope | The kernel, components, and drivers supported by simulation |
| Main purpose | Stabilize the mainline periodically through small releases that support traceability |
| Release frequency | Monthly evaluation, with a human decision on whether to trigger a release |

**Release strategy:**

1. CI runs tests automatically and collects test coverage and pass rates.
2. CI generates a release test report covering coverage, pass rates, functionality introduced by commits since the previous release, and known issues.
3. A release proposal discussion is created automatically to notify core maintainers and invite their input.
4. Core maintainers decide whether to release. A release may be skipped if only a few fixes or optimizations have accumulated during the period.

The overall pass rate does not have to reach 100%, but known issues must be listed so maintainers can assess them before making the release decision.

## 5. Version Planning Process

See the [Release Process](release_process_en.md) for release stages and responsibilities.

```text
A requirement or PR proposes a version classification
    -> Module maintainer makes an initial assessment
    -> Core maintainer group reviews high-risk changes
    -> Changes enter the release milestone
    -> X.Y is confirmed before feature freeze
    -> X.Y.Z is confirmed before release
    -> Release owner creates the tag and release
```

### 5.1 Release Preparation

- Collect unresolved issues from the previous release, community requirements, and new features.
- Assign an initial `X`, `Y`, or `Z` classification based on feature impact.
- Create a release milestone that distinguishes mandatory, deferrable, and excluded items.
- Assign the release owner, module maintainers, target platforms, and test owners.
- Plan `Z` releases backward from a one-month cycle. For `Y` releases, choose a 3–6 month cycle according to feature scope and available resources. Confirm test capabilities and maintenance staffing before defining the feature scope.

### 5.2 Release Development

- PRs adding new features must state the proposed version level and the reason for that classification when they are submitted for merging.
- Module maintainers confirm feature boundaries, compatibility, and test scope.
- If an `X`-level change is identified, reassess the release goals, migration cost, and release date.
- If a new feature cannot form a complete deliverable, keep it on the mainline and defer it to the next release. Do not conceal scope changes by changing the version number.
- Maintain only one `Y` release target per release cycle. Do not accept untested large features at the last minute to meet a release date. Defer features that have not completed validation to the next release.

### 5.3 Feature Freeze

- Begin stabilizing fixes for a `Z` release approximately one month before release. Begin stabilizing features for a `Y` release approximately one month before release, and confirm `X.Y` before the freeze.
- After the freeze, do not add features, public APIs, components, or framework capabilities.
- After the freeze, allow only fixes for release blockers, necessary security fixes, and corrections to release materials.
- Remove `X`- or `Y`-level changes discovered after the freeze from the current release. Replan them for a major release or the next minor release on a 3–6 month cycle, respectively.

### 5.4 Official Release

- Set the release version to `X.Y.0`, or to `X.Y.Z` on a stable branch.
- The release owner checks consistency across version macros, the Git tag, the release, the changelog, and deliverables.
- If an issue is found after publication, publish a new `X.Y.Z+1` release. Do not modify the original tag, release contents, or deliverables.

### 5.5 Release Cadence

| Cycle | Main activity |
| --- | --- |
| 1 month | Publish a `Z` release focused on defects, security issues, local optimizations, and BSP adaptations |
| 3–6 months | Publish a `Y` release when its feature set, test scope, and maintenance resources meet the requirements |
| `X` releases | Plan separately according to readiness for kernel, framework, or system-level upgrades, without a fixed cycle |

No release type requires a fixed publication date. A release may be deferred if blockers remain within its guaranteed support scope. Do not force a release by reducing promised testing, narrowing the support scope, or skipping reviews of high-risk changes. Once the cycle for a `Y` release is selected, do not shorten it to accommodate last-minute features.

## 6. Compatibility and Migration Requirements

The following changes require a compatibility review:

- Public interfaces and behavior of thread scheduling, IPC, timers, memory management, interrupts, or SMP.
- Device driver interfaces, BSP initialization, Kconfig, default configurations, and component configuration formats.
- File systems, network stacks, package APIs, error codes, blocking semantics, and interrupt context restrictions.
- Structure layouts, the ABI, toolchain requirements, default stack sizes, heap layouts, and critical resource usage.

Compatibility changes must record affected users or components, migration methods, representative BSPs, and known limitations. `X` releases must provide migration instructions. `Y` and `Z` releases must also explicitly document changes to default behavior or resource usage in the release notes.

## 7. Release Checklist

- [ ] The release milestone defines mandatory scope and release goals.
- [ ] All included changes have an `X/Y/Z` classification.
- [ ] The core maintainer group has approved all `X`-level changes.
- [ ] `Y`-level features are independently deliverable and have completed testing.
- [ ] `Z`-level changes introduce no new public APIs, complete components, or framework capabilities.
- [ ] No unapproved feature changes have occurred after the freeze.
- [ ] `RT_VERSION_MAJOR/MINOR/PATCH` matches the Git tag.
