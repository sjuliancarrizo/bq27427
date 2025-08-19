# About `bq27427`

This is a template repository for `esp-idf-lib` component. The repository is
intended to be cloned to create new component quickly.

> [!IMPORTANT]
> This instruction is intended for `esp-idf-lib` members. You may use this
> template component for your own under your GitHub account. However, the CI
> will NOT work.

The up-to-date version of this document can be found at
[bq27427](https://github.com/esp-idf-lib/bq27427/tree/main).

<!-- vim-markdown-toc GFM -->

* [Features](#features)
* [Using the template](#using-the-template)
    * [Creating a repository from the template](#creating-a-repository-from-the-template)
    * [Clone the repository](#clone-the-repository)
    * [Verifying the template works](#verifying-the-template-works)
    * [Starting development](#starting-development)
    * [Enable GitHub Pages](#enable-github-pages)
* [Obtain an access token of ESP Component Registry](#obtain-an-access-token-of-esp-component-registry)
* [Initial commit](#initial-commit)
    * [Code style](#code-style)
    * [Rules](#rules)
* [CI](#ci)
* [Linking the component repository to `core` repository](#linking-the-component-repository-to-core-repository)

<!-- vim-markdown-toc -->

## Features

* CI is enabled by default
* The documentation is published to GitHub Pages
* The component is published to ESP Component Repository when released

## Using the template

In this section, you will create a new component, `foo`. Replace `foo` with
the real name of the component.

### Creating a repository from the template

Follow the official documentation,
[Creating a repository from a template](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template#creating-a-repository-from-a-template).

1. Choose [Owner] under [General]. If you are a member of `esp-idf-lib`, choose
  `esp-idf-lib`. If not, choose your GitHub account.
1. Type `foo` in [Repository name].
1. Describe the component in [Description].
1. Choose [Public] in [Choose visibility].
1. Click [Create repository]

### Clone the repository

Clone the new repository as usual.

```console
git clone git@github.com:esp-idf-lib/foo.git
cd foo
```

> [!IMPORTANT]
> Check out the `git` `submodule` after cloning the repository on local machine.

```console
git submodule update --init --recursive
```

### Verifying the template works

In the new repository directory, build an example to verify the template is
working.

```console
cd examples/example1
```

Edit `main/idf_component.yml` by replacing `bq27427` under
`dependencies` with the component name.

```console
vim main/idf_component.yml
```

```diff
--- a/examples/example1/main/idf_component.yml
+++ b/examples/example1/main/idf_component.yml
@@ -3,6 +3,6 @@
 version: 1.0.0
 description: Example 1
 dependencies:
-  esp-idf-lib/bq27427:
+  esp-idf-lib/foo:
     version: "~1.0.0"
     override_path: ../../../
```

Then, build the example.

```
idf.py all
```

The build should succeed.

### Starting development

Find and replace ALL occurrences of `bq27427` in the repository
with the component name.

If you have [ack] installed, here is the command to list all the files to
modify:

```console
ack --files-with-matches --ignore-dir build bq27427 .
```

Next, rename template source files.

```console
mv bq27427.c foo.c
mv include/bq27427.h include/foo.h
```

Commit and push all files.

```console
git add .
git push
```

Visit the repository page. Click [Actions] > [Build examples] in the side menu
at left. Click [Run workflow] utton. This runs [Build examples] workflow on
`main` branch. The workflow should succeeds without errors (it takes 10
minutes or so to finish).

Now the repository is ready. Implement the driver in the C header file and C
files.

Code style is enforced. See
[Espressif IoT Development Framework Style Guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/contribute/style-guide.html).

Edit `README.md` and `docs/index.rst`.

Things should be documented:

* What the chip or the component does
* The URL of the data sheet
* How to use the component in short
* Example code

Edit `.eil.yml`.

1. Replace `name` with the component name.
1. Describe the component in `description`. One sentence.
1. `version` should be `0.x.x` (replace `x` with whatever minor and patch
   version in integer). When linking the component to
   `esp-idf-lib/core`, The version will become `1.0.0`.
1. Update `code_owners` with your name.
1. Choose one or more `groups`. See available groups at:
   [groups.yml](https://github.com/esp-idf-lib/core/blob/main/groups.yml)
1. Update `depends` with components your component depends on. If none, add
   `freertos`.
1. `targets` should be all ESP32 targets and optionally `esp8266`.
1. Make sure `license` matches your chosen license. See acceptable licenses at:
   [How to contribute to esp-idf-lib](https://github.com/esp-idf-lib/core/blob/main/CONTRIBUTING.md).
    No GPL licenses.
1. Update `copyrights` with your name.

> [!IMPORTANT]
> If your name is not in [persons.yml](https://github.com/esp-idf-lib/core/blob/main/persons.yml),
> contact `esp-idf-lib` admins and request to add your name in the file.

Edit `idf_component.yml`.

* `targets` MUST be ESP32 targets only. No `esp8266`. `esp8266` is not
  supported by the ESP Component Registry.
* Make sure `license` matches your chosen license
* Update `dependencies`.

See
[idf_component.yml Manifest File](https://docs.espressif.com/projects/idf-component-manager/en/latest/reference/manifest_file.html)
for more details.

### Enable GitHub Pages

> [!NOTE]
> Please ask @trombik for help when you are stacked in this section.

Visit the GitHub repository, [Settings], [Pages] in the side menu at left, and
choose [GitHub Actions] as [Source] under [Build and deployment]. This enables
deployment HTML files from GitHub Actions.

With `gh` CLI, the following commands do the same above.

```sh
gh api /repos/esp-idf-lib/${REPO}/pages -X POST -F build_type=workflow
```

Next, visit [Environments] in the side menu at left, click `github-pages`.

1. In [Configure github-pages], click [Add deployment branch or tag rule] under
   [Deployment branches and tags].
1. In [Add deployment branch or tag rule] dialog, choose [Tag] for [Ref type].
   Type `*.*.*` in [Name pattern].
1. Click [Add rule].

With `gh` CLI, the following command does the same above.

```sh
gh api --method POST /repos/esp-idf-lib/${REPO}/environments/github-pages/deployment-branch-policies -f 'name=*.*.*' -f "type=tag"
```

To see the `branch_policies`, run:

```sh
gh api /repos/esp-idf-lib/bq27427/environments/github-pages/deployment-branch-policies
```

The output should be like below:

```json
{
  "total_count": 2,
  "branch_policies": [
    {
      "id": 32966213,
      "node_id": "MDE2OkdhdGVCcmFuY2hQb2xpY3kzMjk2NjIxMw==",
      "name": "main",
      "type": "branch"
    },
    {
      "id": 33644461,
      "node_id": "MDE2OkdhdGVCcmFuY2hQb2xpY3kzMzY0NDQ2MQ==",
      "name": "*.*.*",
      "type": "tag"
    }
  ]
}
```

For more about the API environment, see
[REST API endpoints for deployment branch policies](https://docs.github.com/en/rest/deployments/branch-policies?apiVersion=2022-11-28).

## Obtain an access token of ESP Component Registry

> [!NOTE]
> This section is only for organization admin. The token described below is
> already set at organization level. If you are not an `esp-idf-lib` admin,
> skip this section.

To automate uploading a component to ESP Component Registry with GitHub
Actions workflow, you need:

* to be an admin of the component on ESP Component Registry
* to have a privilege to set Actions secrets and variables in the GitHub
  repository.

Contact @trombik if you don't or are not sure.

To use a workflow to upload the component when the component has been released,
you need an access token of ESP Component Registry. The token is used in a
workflow via GitHub secrets.


1. Visit [ESP Component Registry](https://components.espressif.com/) and
   login.
1. Click your profile menu on top and click [Tokens]
1. In [Create new access token] page, fill in [Description], e.g. "Uploading
   component from GitHub Action".
1. Select [write:component] in [Scopes of the token].
1. Click [Create]
1. In [Access token successfully created] page, copy the generated access
   token. Please keep it secret and do not publish it anywhere. This token is
   used in the next step and shown just once.

Next, create a GitHub secret in the repository.

1. Visit the component repository on GitHub.
1. Click [Settings]
1. Click [Secrets and variables] in the side menu at left.
1. Under [Repository secrets], click [New repository secret]
1. In [Actions secrets / New secret] page, fill in [Name] with `ESP_TOKEN`
1. Paste the access token value from the previous step into [Secret].
1. Click [Add secret].
1. Make sure the token name, `ESP_TOKEN`, is shown in [Repository secrets]

## Initial commit

After all of the above, you can start committing and pushing your code to the
repository.

For documenting the component, see `docs` directory.

### Code style

Please see
[Espressif IoT Development Framework Style Guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/contribute/style-guide.html).

To format code, use `astyle`.

```console
astyle --project --recursive '*.c,*.h'
```

> [!NOTE]
> The rules are defined in `.astylerc`.

### Rules

> [!NOTE]
> The rules are not not exhaustive.

Use `esp_err_t` for return value to signal errors.

```c
/* GOOD */

#include <esp_err.h>
#include <esp_log.h>

#define TAG "foo"

esp_err_t func(uint8_t value)
{
    if (value == 0) {
        ESP_LOGE(TAG, "value must not be zero");
        return ESP_ERR_INVALID_ARG;
    }
    reurn ESP_OK;
}
```

```c
/* BAD */

#include <esp_log.h>

#define TAG "foo"

int func(uint8_t value)
{
    if (value == 0) {
        ESP_LOGE(TAG, "value must not be zero");
        return -1;
    }
    reurn 1;
}
```

Always check NULL pointers before use.

```c
/* GOOD */

#include <esp_err.h>
#include <esp_check.h>

#define TAG "foo"

esp_err_t func(uint8_t *values, size_t size)
{
    ESP_RETURN_ON_FALSE(values, ESP_ERR_INVALID_ARG, TAG, "values is NULL");
    /* do something with values */

    return ESP_OK;
}
```

```c
# BAD

#include <esp_err.h>

#define TAG "foo"

esp_err_t func(uint8_t *values, size_t size)
{
    /* do something with values */

    return ESP_OK;
}
```

Use label when something must always be done.

```c
/* GOOD */

#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>

#define TAG "foo"

esp_err_t func()
{
    esp_err_t ret = ESP_FAIL;

    /* do something, such as obtaining a lock */
    ret = do_something();
    ESP_GOTO_ON_ERROR(ret, fail, TAG, "something failed");

    ret = ESP_OK;
fail:
    /* do some cleanup, such as releasing a lock */
    cleanup();
    return ret;
}
```

```c
/* BAD */

#include <esp_err.h>
#include <esp_log.h>

#define TAG "foo"

esp_err_t func()
{
    esp_err_t ret = ESP_FAIL;

    /* do something, such as obtaining a lock */
    ret = do_something();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "something failed");
        cleanup();
        return ret;
    }

    ret = ESP_OK;
    /* do some cleanup, such as releasing a lock */
    cleanup();
    return ret;
}
```

Use macros or variables instead of magic values.

```c
/* GOOD */

#include <esp_err.h>

#define COMMAND_START 0xff
#define COMMAND_STOP  0x00

esp_err_t func(uint8_t value)
{
    ret = ESP_FAIL;

    /* start processing with value */
    ret = do_something(COMMAND_START, value);
    return ret;
}
```

```c
/* BAD */

#include <esp_err.h>

esp_err_t func(uint8_t value)
{
    ret = ESP_FAIL;

    /* start processing with value */
    ret = do_something(0xff, value);
    return ret;
}
```

Use `const` when the function does not modify arguments.

```c
/* GOOD */

uint32_t add(const uint8_t a, const uint8_t b)
{
    return a + b;
}
```

```c
/* BAD */

uint32_t add(uint8_t a, uint8_t b)
{
    return a + b;
}
```

## CI

CI is enabled by default. All the GitHub Actions workflows are managed by a
repository,
[esp-idf-lib/shared-workflows](https://github.com/esp-idf-lib/shared-workflows/).

Here is some workflows (not exhaustive):

* `build.yml` builds all the examples.
* `build-docs.yml` builds and publish documentation on GitHub Pages.
* [validate-esp-idf-lib-component](https://github.com/esp-idf-lib/validate-esp-idf-lib-component/)
  validates a component. There are many tests under
  [spec](https://github.com/esp-idf-lib/validate-esp-idf-lib-component/tree/main/spec)
  directory.
* `publish-esp-component-registry.yml` publishes the component to ESP
  Component Registry when released with tag. The tag must be the version.

## Linking the component repository to `core` repository

The component is now ready. However, the component is not linked to
`esp-idf-lib/core`, where all the components are managed.

Contact `esp-idf-lib` admins to link the component.
