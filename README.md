# Akela-IgnoranceIsBliss

The `IgnoranceIsBliss` plugin provides an easy way to ignore certain keys on the
keyboard. Intended to be used on janky prototypes, where pressing one key ofter
triggers another - and we want to ignore the other one.

## Using the Plugin

To use the plugin, we must include the header, and tell the `IgnoranceIsBliss`
plugin which keys to ignore. It should be the first plugin used, so it has a
chance to ignore keys before anything else gets to it.

```c++
#include <Akela-IgnoranceIsBliss.h>

void setup (void) {
  IgnoranceIsBliss.configure (R0C6 | R2C6, R0C15);

  Keyboardio.setup (KEYMAP_SIZE);
  Keyboardio.use (&IgnoranceIsBliss, NULL);
}
```

## Plugin methods

The plugin provides an `IgnoranceIsBliss` singleton object, with the following
method:

### `.configure(leftHandIgnores, rightHandIgnores)`

> Configures the extension to ignore the given keys. Both the left- and
> right-hand sides must be an OR-ed list of `RxCy` constants.

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/Akela-Plugins/Akela-IgnoranceIsBliss/blob/master/examples/IgnoranceIsBliss/IgnoranceIsBliss.ino
