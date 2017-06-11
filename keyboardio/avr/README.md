# Arduino Core for the Keyboardio Model 01

This repository contains a number of git submodules.

As an end-user, you can recursively check out all the referenced modules:

```
% make checkout-submodules
```

As a maintainer, you can pull all the referenced modules to the latest upstream 
tips of the modules' canonical branches:

```
% make maintainer-update-submodules
```

Do note that in order to commit the changes to the submodules of a given repository, 
you'll need to commit and push the changes in that repository

To add a submodule, use a commandline like this:

```
% git submodule add https://github.com/Keyboardio/Kaleidoscope-Plugin/ libraries/Kaleidoscope-Plugin
```
