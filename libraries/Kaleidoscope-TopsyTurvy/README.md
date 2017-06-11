# Kaleidoscope-TopsyTurvy

![status][st:stable] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-TopsyTurvy.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-TopsyTurvy

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

`TopsyTurvy` is a plugin that inverts the behaviour of the `Shift` key for some
selected keys. That is, if configured so, it will input `!` when pressing the
`1` key without `Shift`, but with the modifier pressed, it will input the
original `1` symbol.

## Using the plugin

To use the plugin, one needs to include the header, mark keys to apply plugin
effects to, and use the plugin:

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-TopsyTurvy.h>

// In the keymap:
TOPSY(1), TOPSY(2), TOPSY(3)

void setup () {
  USE_PLUGINS (&TopsyTurvy);

  Kaleidoscope.setup ();
}
```

## Keymap markup

There is only one macro that the plugin provides, which one can use in keymap definitions:

### `TOPSY(key)`

> Mark the specified `key` (without the `Key_` prefix!) for TopsyTurvy, and swap
> the effect of `Shift` when the key is used. One can have any number of
> topsy-turvy keys on a keymap.
>
> The keys must be plain old keys, modifiers or anything other augmentation
> cannot be applied.

The plugin provides a number of macros one can use in keymap definitions:

## Plugin methods

The plugin provides the `TopsyTurvy` object, without any public methods or properties.

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/keyboardio/Kaleidoscope-TopsyTurvy/blob/master/examples/TopsyTurvy/TopsyTurvy.ino
