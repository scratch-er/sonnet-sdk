# Candle

A candle flame flicker demo. A small three-parameter flame model is rendered as
ASCII brightness bars over the UART and mapped to 6 PWM LED channels, while
random noise makes the flame flicker and buttons let you "blow" on it.

## How it works

The flame shape is a Lorentzian curve over 6 sample positions, controlled by a
3-parameter state (`flame.h`):

- `a` — amplitude
- `b` — width
- `c` — center

Each ~100 ms frame (`main.c`):

1. Brightness is sampled at 6 positions and printed as a bar like `[.~-+*#]`
   followed by `Hello, SimpleSoc!`.
2. The inverted brightness values are written as duty cycles to 6 timer PWM
   channels (TIMER0 ch 0–3, TIMER1 ch 0–1) to drive LEDs.
3. Four active-low buttons on GPIO0 pins 0–3 apply a directional "wind" input
   that pushes the flame's amplitude, width, and center (`apply_input`,
   using `force_add`/`force_mul`).
4. A random disturbance (`apply_disturbance`) makes the flame flicker.
5. A feedback term (`apply_feedback`) pulls the state back toward its rest
   values, so the flame recovers after being blown.

All math is done in Q32.16 fixed point (`fixed_math.h`), so no FPU is needed.

## Files

- `main.c` — main loop, UART/PWM output, button input
- `flame.c` / `flame.h` — flame model: shape, input forces, disturbance, feedback
- `fixed_math.c` / `fixed_math.h` — Q32.16 fixed-point arithmetic and random numbers

## Requirement

This example requires the `simplesoc-sram` (default) or `simplesoc` BSP.
