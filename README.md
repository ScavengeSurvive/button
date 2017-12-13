# Button

A simple framework using streamer areas and key checks to give the in-game effect of physical buttons that players must press instead of using a command. It was created as an alternative to the default GTA:SA spinning pickups for a few reasons:

* A player might want to stand where a pickup is but not use it (if the pickup is a building entrance or interior warp, he might want to stand in the doorway without being teleported.)
* Making hidden doors or secrets that can only be found by walking near the button area and seeing the textdraw. (or spamming F!)
* Spinning objects don't really add immersion to a role-play environment!

## Installation

Simply add to your `pawn.json`/`pawn.yaml`:

```json
{
    "dependencies": ["ScavengeSurvive/button"]
}
```

Update your `dependencies` directory:

```bash
sampctl package ensure
```

Include in your code and begin using the library:

```pawn
#include <button>
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.
