OpenSBI Contribution Guideline
==============================

All contributions to OpenSBI can be sent in the following ways:
1. Email patches to the OpenSBI mailing list at `opensbi@lists.infradead.org`
2. GitHub Pull Requests (PRs) to the [OpenSBI main repository]

To join the OpenSBI mailing list, please visit the [OpenSBI infradead page].

The OpenSBI maintainers prefer patches via the OpenSBI mailing list
(option 1 above) so that they are visible to a wider audience. All
accepted patches on the OpenSBI mailing list will be taken by any of
the OpenSBI maintainers and merged into the [OpenSBI main repository]
using GitHub PRs.

All contributed work must follow the following rules:
1. OpenSBI code should be written in accordance to the [Linux coding style].
2. This project embraces the [Developer Certificate of Origin (DCO)] for
contributions. This means that you must agree to the following prior to
submitting patches: if you agree with this developer certificate you
acknowledge this by adding a Signed-off-by tag to your patch commit log.
Every submitted patch must have this tag.
3. A commit message must have a subject line, followed by a blank line,
followed by a description of the patch content. A blank line and the author
Signed-off-by tag must follow this description.
4. A commit subject line must start with a prefix followed by a ":". Common
prefixes are for example "lib:", "platform:", "firmware:", "docs:", "utils:"
and "top:".
5. Maintainers should use "Rebase and Merge" when using GitHub to merge pull
requests to avoid creating unnecessary merge commits.
6. Maintainers should avoid creating branches directly in the main
riscv/opensbi repository. Instead prefer using a fork of the riscv/opensbi main
repository and branches within that fork to create pull requests.
7. A maintainer cannot merge his own pull requests in the riscv/opensbi main
repository.
8. A pull request must get at least one review from a maintainer.
9. A pull request must spend at least 24 hours in review to allow for other
developers to review.

-----------------------------------------------------------------------

Developer Certificate of Origin
Version 1.1

Copyright (C) 2004, 2006 The Linux Foundation and its contributors.
660 York Street, Suite 102,
San Francisco, CA 94110 USA

Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.


Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.

-----------------------------------------------------------------------

[OpenSBI main repository]: https://github.com/riscv/opensbi
[OpenSBI infradead page]: http://lists.infradead.org/mailman/listinfo/opensbi
[Linux coding style]: https://www.kernel.org/doc/html/v4.10/process/coding-style.html
[Developer Certificate of Origin (DCO)]: http://developercertificate.org/
