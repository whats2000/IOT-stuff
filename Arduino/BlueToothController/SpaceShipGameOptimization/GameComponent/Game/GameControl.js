/**
 * Represents a controller for handling game input key states.
 */
class GameControl {
    /**
     * Initializes the GameControl instance.
     */
    constructor() {
        this.setupEventListeners();

        this.useMouseControl = false; // Indicates whether the game uses mouse control.
        this.alwaysFire = false;      // Indicates whether the player always fires missiles.
        this.toggleHold = true;       // Initialize the toggle hold setting state as true (or false if you want it initially off).


        // Initialize mouse state
        this.mouseLeftClick = false;  // Indicates whether the left mouse button is currently clicked.
        this.currentMouseX = 0;       // The current X-coordinate of the mouse cursor.
        this.currentMouseY = 0;       // The current Y-coordinate of the mouse cursor.

        // Initialize WebSocket connection
        this.setupWebSocket();
    }


    /**
     * Set up event listeners to handle key presses and releases.
     */
    setupEventListeners() {
        document.addEventListener("keydown", (event) => this.handleKeyEvent(event, true));
        document.addEventListener("keyup", (event) => this.handleKeyEvent(event, false));
        document.addEventListener("mousedown", (event) => this.handleMouseDown(event));
        document.addEventListener("mouseup", (event) => this.handleMouseUp(event));
        document.addEventListener("mousemove", (event) => this.handleMouseMove(event));
        document.getElementById("mouse-control-toggle").addEventListener("change", this.toggleMouseControl.bind(this));
        document.getElementById("always-fire-toggle").addEventListener("change", this.toggleAlwaysFire.bind(this));
        document.getElementById("hold-to-toggle-shield-toggle").addEventListener("change", () => {
            this.toggleHold = !this.toggleHold; // Toggle the toggle hold setting state
        });
    }

    /**
     * Handle key events and update key states accordingly.
     * @param {KeyboardEvent} event - The keyboard event.
     * @param {boolean} isPressed - Indicates if the key is pressed (true) or released (false).
     */
    handleKeyEvent(event, isPressed) {
        const key = this.getKeyName(event);

        if (key) {
            this.keyStates[key] = isPressed;
        }
    }

    /**
     * Handle mouse down event.
     * @param {MouseEvent} event - The mouse event.
     */
    handleMouseDown(event) {
        if (event.button === 0) {
            // Left mouse button click
            this.mouseLeftClick = true;
        }
    }

    /**
     * Handle mouse up event.
     * @param {MouseEvent} event - The mouse event.
     */
    handleMouseUp(event) {
        if (event.button === 0) {
            // Left mouse button release
            this.mouseLeftClick = false;
        }
    }

    /**
     * Handle mouse move event to update the current mouse position.
     * @param {MouseEvent} event - The mouse event.
     */
    handleMouseMove(event) {
        this.currentMouseX = event.clientX;
        this.currentMouseY = event.clientY;
    }

    /**
     * Map a keyboard event to its corresponding key state property.
     * @param {KeyboardEvent} event - The keyboard event.
     * @returns {string|null} - The name of the corresponding key state property or null if not mapped.
     */
    getKeyName(event) {
        const keyMap = {
            ArrowUp: "isArrowUpPressed",
            ArrowDown: "isArrowDownPressed",
            ArrowLeft: "isArrowLeftPressed",
            ArrowRight: "isArrowRightPressed",
            " ": "isSpacePressed",
            Escape: "isEscapePressed",
            Shift: "isShiftPressed",
            Enter: "isEnterPressed"
        };

        return keyMap[event.key] || null;
    }

    /**
     * Default values for key states.
     * @type {Object}
     */
    keyStates = {
        isArrowUpPressed: false,
        isArrowDownPressed: false,
        isArrowLeftPressed: false,
        isArrowRightPressed: false,
        isSpacePressed: false,
        isEscapePressed: false,
        isShiftPressed: false,
        isEnterPressed: false
    };

    /**
     * Handle the change event for the mouse control toggle.
     */
    toggleMouseControl() {
        this.useMouseControl = document.getElementById("mouse-control-toggle").checked;
    }

    /**
     * Handle the change event for the always-fire mode toggle.
     */
    toggleAlwaysFire() {
        this.alwaysFire = document.getElementById("always-fire-toggle").checked;
    }

    /**
     * Set up a WebSocket connection and handle incoming messages.
     */
    setupWebSocket() {
        const ws = new WebSocket("ws://127.0.0.1:9001");
        ws.onmessage = (event) => {
            this.handleWebSocketMessage(event.data);
        };
    }

    /**
     * Handle messages from the WebSocket connection.
     * @param {string} data - The incoming message as a string.
     */
    handleWebSocketMessage(data) {
        // Parse the data and update game controls
        // Example format: "X:100,Y:150,Enter:0,Esc:1,Shift:0,Fire:1"
        const controls = data.split(',').reduce((acc, curr) => {
            const [key, value] = curr.split(':');
            acc[key.trim()] = parseInt(value, 10);
            return acc;
        }, {});

        // Update key states based on the controls
        this.keyStates.isArrowRightPressed = controls['X'] > 20;
        this.keyStates.isArrowLeftPressed = controls['X'] < -20;

        // Invert Y-axis
        this.keyStates.isArrowDownPressed = controls['Y'] < -20;  // Inverted
        this.keyStates.isArrowUpPressed = controls['Y'] > 20;     // Inverted

        this.keyStates.isEnterPressed = controls['Enter'] === 0;
        this.keyStates.isEscapePressed = controls['Esc'] === 0;
        this.keyStates.isShiftPressed = controls['Shift'] === 0;
        this.keyStates.isSpacePressed = controls['Fire'] === 0;
    }
}

export default GameControl;
