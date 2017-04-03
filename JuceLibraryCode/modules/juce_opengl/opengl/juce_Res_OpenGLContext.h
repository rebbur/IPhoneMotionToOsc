#ifndef __JUCE_RES_OPENGLCONTEXT_JUCEHEADER__
#define __JUCE_RES_OPENGLCONTEXT_JUCEHEADER__

#include "juce_OpenGLPixelFormat.h"
#include "../native/juce_OpenGLExtensions.h"
#include "juce_OpenGLRenderer.h"

class JUCE_API  ResOpenGLContext
{
public:
    ResOpenGLContext();

    /** Destructor. */
    virtual ~ResOpenGLContext();

    //==============================================================================
    /** Gives the context an OpenGLRenderer to use to do the drawing.
        The object that you give it will not be owned by the context, so it's the caller's
        responsibility to manage its lifetime and make sure that it doesn't get deleted
        while the context may be using it. To stop the context using a renderer, just call
        this method with a null pointer.
        Note: This must be called BEFORE attaching your context to a target component!
    */
    void setRenderer (OpenGLRenderer* rendererToUse) noexcept;

    /** Sets the pixel format which you'd like to use for the target GL surface.
        Note: This must be called BEFORE attaching your context to a target component!
    */
    void setPixelFormat (const OpenGLPixelFormat& preferredPixelFormat) noexcept;

    /** Provides a context with which you'd like this context's resources to be shared.
        The object passed-in here is a platform-dependent native context object, and
        must not be deleted while this context may still be using it! To turn off sharing,
        you can call this method with a null pointer.
        Note: This must be called BEFORE attaching your context to a target component!
    */
    void setNativeSharedContext (void* nativeContextToShareWith) noexcept;

    //==============================================================================
    /** Attaches the context to a target component.

        If the component is not fully visible, this call will wait until the component
        is shown before actually creating a native context for it.

        When a native context is created, a thread is started, and will be used to call
        the OpenGLRenderer methods. The context will be floated above the target component,
        and when the target moves, it will track it. If the component is hidden/shown, the
        context may be deleted and re-created.
    */
    void attachTo (Component& component);

    /** Detaches the context from its target component and deletes any native resources.
        If the context has not been attached, this will do nothing. Otherwise, it will block
        until the context and its thread have been cleaned up.
    */
    void detach();

    /** Returns true if the context is attached to a component and is on-screen.
        Note that if you call attachTo() for a non-visible component, this method will
        return false until the component is made visible.
    */
    bool isAttached() const noexcept;

    /** Returns the component to which this context is currently attached, or nullptr. */
    Component* getTargetComponent() const noexcept;

    //==============================================================================
    /** Makes this context the currently active one.
        You should never need to call this in normal use - the context will already be
        active when OpenGLRenderer::renderOpenGL() is invoked.
    */
    bool makeActive() const noexcept;

    /** Returns true if this context is currently active for the calling thread. */
    bool isActive() const noexcept;

    /** If any context is active on the current thread, this deactivates it.
        Note that on some platforms, like Android, this isn't possible.
    */
    static void deactivateCurrentContext();

    //==============================================================================
    /** Swaps the buffers (if the context can do this).
        There's normally no need to call this directly - the buffers will be swapped
        automatically after your OpenGLRenderer::renderOpenGL() method has been called.
    */
    void swapBuffers();

    /** Sets whether the context checks the vertical sync before swapping.

        The value is the number of frames to allow between buffer-swapping. This is
        fairly system-dependent, but 0 turns off syncing, 1 makes it swap on frame-boundaries,
        and greater numbers indicate that it should swap less often.

        Returns true if it sets the value successfully - some platforms won't support
        this setting.
    */
    bool setSwapInterval (int numFramesPerSwap);

    /** Returns the current swap-sync interval.
        See setSwapInterval() for info about the value returned.
    */
    int getSwapInterval() const;

    //==============================================================================
    /** Returns an OS-dependent handle to some kind of underlting OS-provided GL context.

        The exact type of the value returned will depend on the OS and may change
        if the implementation changes. If you want to use this, digging around in the
        native code is probably the best way to find out what it is.
    */
    void* getRawContext() const noexcept;

	// you need to override these, use rj::OpenGLContext
	virtual void lockNativeContext() = 0;
	virtual void unLockNativeContext() = 0;
	
	//get component peer
	ComponentPeer* getComponentPeer() const noexcept;

	

private:
    class Attachment;
    OpenGLContext::NativeContext* nativeContext;
    OpenGLRenderer* renderer;
    ScopedPointer<Attachment> attachment;
    OpenGLPixelFormat pixelFormat;
    void* contextToShareWith;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResOpenGLContext)
};

#endif