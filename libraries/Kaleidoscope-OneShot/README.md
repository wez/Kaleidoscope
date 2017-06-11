# Kaleidoscope-OneShot

![status][st:stable] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-OneShot.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-OneShot

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

One-shots are a new kind of behaviour for your standard modifier and momentary
layer keys: instead of having to hold them while pressing other keys, they can
be tapped and released, and will remain active until any other key is pressed.
In short, they turn `Shift, A` into `Shift+A`, and `Fn, 1` to `Fn+1`. The main
advantage is that this allows us to place the modifiers and layer keys to
positions that would otherwise be awkward when chording. Nevertheless, they
still act as normal when held, that behaviour is not lost.

Furthermore, if a one-shot key is tapped two times in quick succession, it
becomes sticky, and remains active until disabled with a third tap. This can be
useful when one needs to input a number of keys with the modifier or layer
active, and still does not wish to hold the key down.

To make multi-modifier, or multi-layer shortcuts possible, one-shot keys remain
active if another one-shot of the same type is tapped, so `Ctrl, Alt, b` becomes
`Ctrl+Alt+b`, and `L1, L2, c` is turned into `L1+L2+c`.

## Using the plugin

After adding one-shot keys to the keymap, all one needs to do, is enable the
plugin:

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-OneShot.h>

// somewhere in the keymap...
OSM(LeftControl), OSL(_FN)

void setup() {
  USE_PLUGINS(&OneShot);

  Kaleidoscope.setup();
}
```

## Keymap markup

There are two macros the plugin provides: 

### `OSM(mod)`

> A macro that takes a single argument, the name of the modifier: `LeftCtrl`,
> `LeftShift`, `LeftAlt`, `LeftGUI` or their right-side variant. When marked up
> with this macro, the modifier will act as a one-shot modifier.

### `OSL(layer)`

> Takes a layer number as argument, and sets up the key to act as a one-shot
> layer key.
>
> Please note that while `Kaleidoscope` supports more, one-shot layers are
> limited to 24 layers only.

## Plugin methods

The plugin provides one object, `OneShot`, which implements both one-shot
modifiers and one-shot layer keys. It has the following methods and properties:

### `.isActive()`

> Returns if any one-shot key is in flight. This makes it possible to
> differentiate between having a modifier or layer active, versus having them
> active only until after the next key getting pressed. And this, in turn, is
> useful for macros that need to fiddle with either modifier or layer state: if
> one-shots are not active, they need not restore the original state.

### `.isModifierActive(key)`

> Returns if the modifier `key` has a one-shot state active. Use this together
> with `Keyboard.isModifierActive` to catch cases where a one-shot modifier is
> active, but not registered yet.

### `.cancel([with_stickies])`

> The `cancel()` method can be used to cancel any pending one-shot effects,
> useful when one changed their minds, and does not wish to wait for the
> timeout.
>
> The optional `with_stickies` argument, if set to `true`, will also cancel
> sticky one-shot effects. If omitted, it defaults to `false`, and not canceling
> stickies.

### `.time_out`

> Set this property to the number of milliseconds to wait before timing out and
> cancelling the one-shot effect (unless interrupted or cancelled before by any
> other means).
>
> Defaults to 2500.

### `.hold_time_out`

> Set this property to the number of milliseconds to wait before considering a
> held one-shot key as intentionally held. In this case, the one-shot effect
> will not trigger when the key is released. In other words, holding a one-shot
> key at least this long, and then releasing it, will not trigger the one-shot
> effect.
>
> Defaults to 200.

## Dependencies

* [Kaleidoscope-Ranges](https://github.com/keyboardio/Kaleidoscope-Ranges)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/keyboardio/Kaleidoscope-OneShot/blob/master/examples/OneShot/OneShot.ino
