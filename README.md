# Finite State Robot

This repository contains the Arduino code for a simple line following Robot. The Robot was designed using the Finite State Machine Paradigm and therefore delegates each atomic task to a standalone state.

### The Mission

The robot has a very simple mission: Return the tennis balls to the base.

The steps it takes are as follows:

1. It follows a black trail until it detects the existence of a ball. (Through its ultra-sonic sensors)
2. It attempts to capture the ball.
3. It returns the ball to home base.
4. Repeat From Step one until all balls have been captured.

### Further Development Path

Make the states more modular and allow for code reusability. 