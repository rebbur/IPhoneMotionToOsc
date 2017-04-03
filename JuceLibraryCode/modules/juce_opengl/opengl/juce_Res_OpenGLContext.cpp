class ResOpenGLContext::Attachment  : public ComponentMovementWatcher
{
public:
    Attachment (ResOpenGLContext& c, Component& comp)
       : ComponentMovementWatcher (&comp), context (c)
    {
        if (canBeAttached (comp))
            attach();
    }

    ~Attachment()
    {
        detach();
    }

    void componentMovedOrResized (bool /*wasMoved*/, bool /*wasResized*/)
    {
        Component& comp = *getComponent();

        
        //commented out the code below, we don't want to
        //attach detach to happen without us knowing, let us do this ourselves please
        /*
		bool attached_ = isAttached();
		bool canbe = canBeAttached(comp);
        if (attached_ != canbe)
            componentVisibilityChanged();
        */
        if (comp.getWidth() > 0 && comp.getHeight() > 0
             && context.nativeContext != nullptr)
        {
            if (ComponentPeer* peer = comp.getTopLevelComponent()->getPeer())
                context.nativeContext->updateWindowPosition (peer->getAreaCoveredBy (comp));

        }

    }

    void componentPeerChanged()
    {
        //we actually don't want the detach to happen do we
        //detach();
        componentVisibilityChanged();
    }

    void componentVisibilityChanged()
    {
        //commented out the code below, we don't want to
        //attach detach to happen without us knowing, let us do this ourselves please
        /*
        Component& comp = *getComponent();
        if (canBeAttached (comp))
        {
            if (!isAttached ())
                attach();
        } else {
            detach();
        }
        */
    }

   #if JUCE_DEBUG || JUCE_LOG_ASSERTIONS
    void componentBeingDeleted (Component& component)
    {
        /* You must call detach() or delete your OpenGLContext to remove it
           from a component BEFORE deleting the component that it is using!
        */
        jassertfalse;

        ComponentMovementWatcher::componentBeingDeleted (component);
    }
   #endif

private:
    ResOpenGLContext& context;
    ScopedPointer<OpenGLContext::NativeContext> nativeContext;
	
    static bool canBeAttached (const Component& comp) noexcept
    {
        return comp.getWidth() > 0 && comp.getHeight() > 0 && comp.isShowing();
    }

    bool isAttached () noexcept
    {
        return nativeContext != nullptr;
    }

    void attach()
    {        
        Component& comp = *getComponent();				
		nativeContext = new OpenGLContext::NativeContext (comp, context.pixelFormat, context.contextToShareWith, false, OpenGLContext::defaultGLVersion);

        if (nativeContext->createdOk())
            context.nativeContext = nativeContext;
        else
            nativeContext = nullptr;
		
		if (context.nativeContext != nullptr)
		{
			context.nativeContext->makeActive();

			if (context.renderer != nullptr)
				context.renderer->newOpenGLContextCreated();
		
			//deactivate
			OpenGLContext::deactivateCurrentContext();
		}
		
    }

    void detach()
    {
        if (context.renderer != nullptr)
            context.renderer->openGLContextClosing();

        context.nativeContext = nullptr;
    }
};

ResOpenGLContext::ResOpenGLContext()
    : nativeContext (nullptr), renderer (nullptr), contextToShareWith (nullptr)
{
}

ResOpenGLContext::~ResOpenGLContext()
{
    detach();
}

void ResOpenGLContext::setRenderer (OpenGLRenderer* rendererToUse) noexcept
{
    // This method must not be called when the context has already been attached!
    // Call it before attaching your context, or use detach() first, before calling this!
    jassert (nativeContext == nullptr);

    renderer = rendererToUse;
}

void ResOpenGLContext::setPixelFormat (const OpenGLPixelFormat& preferredPixelFormat) noexcept
{
    // This method must not be called when the context has already been attached!
    // Call it before attaching your context, or use detach() first, before calling this!
    jassert (nativeContext == nullptr);

    pixelFormat = preferredPixelFormat;
}

void ResOpenGLContext::setNativeSharedContext (void* nativeContextToShareWith) noexcept
{
    // This method must not be called when the context has already been attached!
    // Call it before attaching your context, or use detach() first, before calling this!
    jassert (nativeContext == nullptr);

    contextToShareWith = nativeContextToShareWith;
}

void ResOpenGLContext::attachTo (Component& component)
{
    if (getTargetComponent() != &component)
    {
        detach();
        attachment = new Attachment (*this, component);
    }
}

void ResOpenGLContext::detach()
{
    attachment = nullptr;
    nativeContext = nullptr;
}

bool ResOpenGLContext::isAttached() const noexcept
{
    return nativeContext != nullptr;
}

Component* ResOpenGLContext::getTargetComponent() const noexcept
{
    return attachment != nullptr ? attachment->getComponent() : nullptr;
}


bool ResOpenGLContext::makeActive() const noexcept     { return nativeContext != nullptr && nativeContext->makeActive(); }
bool ResOpenGLContext::isActive() const noexcept       { return nativeContext != nullptr && nativeContext->isActive(); }
void ResOpenGLContext::deactivateCurrentContext()      { OpenGLContext::NativeContext::deactivateCurrentContext(); }

void ResOpenGLContext::swapBuffers()
{
    if (nativeContext != nullptr)
        nativeContext->swapBuffers();
}

bool ResOpenGLContext::setSwapInterval (int numFramesPerSwap)
{
    return nativeContext != nullptr && nativeContext->setSwapInterval (numFramesPerSwap);
}

int ResOpenGLContext::getSwapInterval() const
{
    return nativeContext != nullptr ? nativeContext->getSwapInterval() : 0;
}

void* ResOpenGLContext::getRawContext() const noexcept
{
    return nativeContext != nullptr ? nativeContext->getRawContext() : nullptr;
}

ComponentPeer* ResOpenGLContext::getComponentPeer()  const noexcept
{
    #ifdef JUCE_WINDOWS
	return nativeContext != nullptr ? nativeContext->getComponentPeer() : nullptr;
    #else
    return nullptr;
    #endif
}