/**
 * ISOENGINE
 * engine.h
 * 
 * matt.g@castus.tv
 */

#ifndef __ISOENGINE_ISOENGINE_H__
#define __ISOENGINE_ISOENGINE_H__

#include <stdint.h>

typedef enum ISOENGINE_KEYCODE {SPACE, W, A, S, D} ISOENGINE_KEYCODE;

/**
 * A function pointer type for a callback that handles key press events in an isometric engine, taking a starting position (startx, starty),
 * output pointers for the resulting end position (endx, endy), and an isoengine_keycode indicating which key was pressed.
 * This callback pattern allows the engine to compute a new position based on the original coordinates and the specific key input,
 * writing the result back through the endx and endy pointers.
 */
typedef void (*isoengine_keypress_callback)(uint32_t startx, uint32_t starty, uint32_t *endx, uint32_t *endy, const ISOENGINE_KEYCODE keycode);

/**
 * Creates and initializes a new instance of an isometric engine, returning an opaque pointer to the newly created engine object.
 * The caller is responsible for managing the lifetime of the returned object and should release it with the corresponding
 * destroy function when it is no longer needed.
 */
void *isoengine_create();

/**
 * Destroys an isometric engine instance and releases its associated resources.
 * Returns true if the engine was successfully destroyed, or false if the operation failed (e.g., if the provided engine pointer is invalid or NULL).
 */
bool isoengine_destroy(void *engine);

/**
 * isoengine_handle_events processes and dispatches pending events (such as input or system events) for the given isometric engine instance.
 * It returns true if the engine should continue running, or false if a quit/shutdown event was received, signaling the engine loop to terminate.
 */
bool isoengine_handle_events(void *engine);

/**
 * Creates a window for the iso engine with the specified title, dimensions (width and height), and associates it with the given engine instance,
 * returning true on success and false on failure.
 */
bool isoengine_window_create(void *const engine, const char *title, uint16_t width, uint16_t height);

/**
 * Clears and presents the SDL renderer associated with the given isometric engine, effectively drawing a frame. Returns false if the engine or its renderer is null,
 * or if the SDL clear/present operations fail; otherwise returns true.
 */
bool isoengine_render_draw(void *const engine);

/**
 * Creates a new object in the ISO engine and returns a pointer to it.
 * 
 * @param engine Pointer to the isoengine instance. Must not be NULL.
 * @param posx   The X position of the object to create.
 * @param posy   The Y position of the object to create.
 * 
 * @return A pointer to the newly created isoengine_object, or NULL if:
 *         - engine parameter is NULL
 *         - Memory allocation fails when expanding the object buffer
 * 
 * @note The function automatically expands the object buffer in increments
 *       of 1024 objects when needed. The returned pointer points to the
 *       newly allocated object within the engine's object buffer.
 */
void *isoengine_object_create(void *engine, uint32_t posx, uint32_t posy);

/**
 * @brief Registers a keypress callback function for an ISOEngine object.
 * 
 * @param object A pointer to the ISOEngine object that will receive keypress events.
 * @param callback The callback function to be invoked when a keypress event occurs.
 *                 The callback function should match the isoengine_keypress_callback signature.
 * 
 * @return true if the callback was successfully registered, false otherwise.
 * 
 * @note The object pointer must be a valid ISOEngine object instance.
 * @note The callback function must remain valid for the lifetime of the object
 *       or until the callback is unregistered.
 */
bool isoengine_object_keypress_callback(void *object, isoengine_keypress_callback callback);



#endif