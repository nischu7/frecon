# frecon: the Freon Console

This is a terminal emulator that replaces the kernel Virtual Terminal (VT)
console.  It uses the Kernel Mode Setting (KMS) support in the kernel.  It
is similar to the kmscon project:
	https://www.freedesktop.org/wiki/Software/kmscon

A new project was created (rather than re-using kmscon) because:
* We show a boot splash animation during early boot.
* Dynamic VT initialization.
* Integration with CrOS dev mode checks.
* A D-Bus IPC protocol for Chrome to control startup/shutdown.
* VT switching negotiation with Chrome.
* We don't need all the seat logic that kmscon includes.

However, it's not as bad as it sounds!  We haven't re-implemented our own
terminal emulator -- we use the same library that kmscon does:
[libtsm](https://www.freedesktop.org/wiki/Software/libtsm/).  That's the
much more tricky part too.

For even more details, check out the [design doc](./DESIGN-DOC.md) in this
repo.

## Command line options

* `--clear=color`
	Specify clear color for splash screen terminal. The color is 32-bit
integer in a framebuffer format (ARGB) in any format supported by strtoul.
* `--daemon`
	Daemonize frecon.
* `--enable-gfx`
	Enable image and box drawing OSC escape codes.
* `--enable-vts`
	Enable additional terminals in addition to splash screen.
* `--enable-vt1`
	Enable switching to VT1 (aka splash screen) and keep a terminal on it
after finishing splash animation.
* `--frame-interval=N`
	Specify default time (in milliseconds) between frames of splash screen
animation.
* `--gamma=/path/to/gamma/table`
	Specify gamma table to apply. (unimplemented)
* `--loop-start=N`
	Specify frame to start splash animation loop. This option also enables
the animation loop.
* `--loop-count=N`
	Specify number of splash animation loop repetitions.  Default of 0
repeats forever.  Looping has to be enabled using `--loop-start`.
* `--loop-interval=N`
	Specify default time (in milliseconds) between frames of loop animation.
* `--loop-offset=x,y`
	Specify default offset to centered image in loop.
* `--no-login`
	When additional terminals are enabled do not display login prompt on
them. Can be used by scripts to display debugging information and logs on
additional terminals.
* `--num-vts=N`
	Specify number of enabled VTs. The default is 4, the maximum is 12.
* `--offset=x,y`
	Specify absolute location of the splash image on screen.
* `--pre-create-vts`
	Normally VTs are create on demand the the user switches to a VT.
In some cases it may be necessary to pre-create them at startup, for instance
to write a log or debug output for them while they are not active so it can be
examined later. This option allows for that.
* `--print-resolution`
	Print detected screen resolution and exit. Deprecated.
* `--scale=N`
	Set default scale for splash screen images. The scale is a positive
integer number. Default scale is 1. 0 has a special meaning - using scale 1
for screens with horizontal resolution lower and equal than 1920 and 2
otherwise.  Scale affects image/box size and offset.
* `--splash-only`
	Exit immediately after finishing splash animation. Otherwise frecon
will wait for DBUS signal (LoginScreenVisible) from Chrome before exiting
when extra terminals are not enabled.
* `--image=/path/to/image.png`
* `--image-hires=/path/to/image.png`
or any image file name specified after options
	Add image to splash screen animation. `--image` and `--image-hires` are
added conditionally depending whether horizontal screen resolution is below
or above 1920. This allows frecon to make runtime decision which set of images
to use instead running frecon first with `--print-resolution` option and making
this decision in a script that invokes frecon.
Free form image file name in the command line are added unconditionally.

## Imaging escape codes

Frecon implements rudimentary functionality to display images and draw
single color boxes on the terminal screen using OSC (Operating System Command)
based terminal escape codes.

The escape always starts with `\033]` for OSC code and ends with `\033\` ST
code.  Two escapes are implemented, all escape parameters can be specified in
any order.

`image:file=/full/path/to/file.png;location=x,y;offset=x,y;scale=s`

`box:size=w,h;color=c;location=x,y;offset=x,y;scale=s`

* `location` is the absolute location on screen.
* `offset` is an image offset starting with image centered on screen.
* `color` is a 32-bit number in the same format as `--clear` command line
  argument, it defaults to `0`.
* `size` is two integer numbers.
* `scale` is integer scaling factor applied to image size or box size.

Examples:
```sh
echo -ne "\033]image:file=/usr/share/chromeos-assets/images_100_percent/boot_splash_frame18.png\033\\" > /dev/pts/1
echo -ne "\033]box:color=0xFFFFFFFF;size=100,100\033\\" > /dev/pts/1
```

## Files

Frecon creates the following files and links in `/var/run/frecon` directory:

- `/var/run/frecon/pid` which contains pid for frecon daemon process (only when
  `--daemon` is specified on command line).

- for every VT it creates, a link from `/var/run/frecon/vt%u` to `/dev/pts/X`
  where `%u` is terminal number from 0 to num-vts - 1 so the user can determine
  which VT uses which pts since pts number assignment is not deterministic.
