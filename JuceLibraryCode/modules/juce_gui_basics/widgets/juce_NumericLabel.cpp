/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

NumericLabel::NumericLabel (const String& name, const String& labelText)
    : Component (name),
      textValue (labelText),
      lastTextValue (labelText),
      font (15.0f),
      justification (Justification::centredLeft),
      border (1, 5, 1, 5),
      minimumHorizontalScale (0.0f),
      keyboardType (TextEditor::textKeyboard),
      editSingleClick (false),
      editDoubleClick (false),
      lossOfFocusDiscardsChanges (false)
{
    setColour (TextEditor::textColourId, Colours::black);
    setColour (TextEditor::backgroundColourId, Colours::transparentBlack);
    setColour (TextEditor::outlineColourId, Colours::transparentBlack);

    textValue.addListener (this);
}

NumericLabel::~NumericLabel()
{
    textValue.removeListener (this);

    if (ownerComponent != nullptr)
        ownerComponent->removeComponentListener (this);

    editor = nullptr;
}

//==============================================================================
String NumericLabel::stripTrailingZeros(const String& text)
{
    //retain possible suffix
// BEGIN_MODIFIED_BY_RESOLUME
    String suffix = text.removeCharacters("-/.0123456789"); // added "/"
    //
    String value = text.initialSectionContainingOnly("-/.0123456789"); // added "/"
// END_MODIFIED_BY_RESOLUME
    
    //we assume this label is used for numbers ;-)
    //if there are only zero's behind the decimal point strip them
    if (value.fromFirstOccurrenceOf(".", false, false).containsOnly("0"))
    {
        value = value.upToFirstOccurrenceOf(".", false, false);
        
		if (value.containsOnly("-0"))
			//strip possible preceding '-' to prevent '-0'
			value = value.removeCharacters("-");
		
    }
    
    return value + suffix;
}

void NumericLabel::setText (const String& newText,
                     const NotificationType notification)
{
    hideEditor (true);

    // BEGIN_MODIFIED_BY_RESOLUME  
    //we assum this label is used for numbers
    //if there are only zero's behind the decimal point strip them
    String text = stripTrailingZeros(newText);
    
    if (lastTextValue != text || fullTextValue != text)
    {
		if(fullTextValue.isEmpty())
			fullTextValue = lastTextValue;
        // END_MODIFIED_BY_RESOLUME
        
        lastTextValue = text;
        textValue = text;
        repaint();

        textWasChanged();

        if (ownerComponent != nullptr)
            componentMovedOrResized (*ownerComponent, true, true);

        if (notification != dontSendNotification)
            callChangeListeners();
    }
}

String NumericLabel::getText (const bool returnActiveEditorContents) const
{
    return (returnActiveEditorContents && isBeingEdited())
                ? editor->getText()
                : textValue.toString();
}

// BEGIN_MODIFIED_BY_RESOLUME
String NumericLabel::getFullText() const
{
	return fullTextValue;
}

void NumericLabel::setFullText(const String& newText)
{
    String text = stripTrailingZeros(newText);
	if(fullTextValue != text)
		fullTextValue = text;
}
// END_MODIFIED_BY_RESOLUME

void NumericLabel::valueChanged (Value&)
{
    if (lastTextValue != textValue.toString())
        setText (textValue.toString(), sendNotification);
}

//==============================================================================
void NumericLabel::setFont (const Font& newFont)
{
    if (font != newFont)
    {
        font = newFont;
        repaint();
    }
}

Font NumericLabel::getFont() const noexcept
{
    return font;
}

void NumericLabel::setEditable (const bool editOnSingleClick,
                         const bool editOnDoubleClick,
                         const bool lossOfFocusDiscardsChanges_)
{
    editSingleClick = editOnSingleClick;
    editDoubleClick = editOnDoubleClick;
    lossOfFocusDiscardsChanges = lossOfFocusDiscardsChanges_;

    setWantsKeyboardFocus (editOnSingleClick || editOnDoubleClick);
    setFocusContainer (editOnSingleClick || editOnDoubleClick);
}

void NumericLabel::setJustificationType (Justification newJustification)
{
    if (justification != newJustification)
    {
        justification = newJustification;
        repaint();
    }
}

void NumericLabel::setBorderSize (BorderSize<int> newBorder)
{
    if (border != newBorder)
    {
        border = newBorder;
        repaint();
    }
}

//==============================================================================
Component* NumericLabel::getAttachedComponent() const
{
    return static_cast<Component*> (ownerComponent);
}

void NumericLabel::attachToComponent (Component* owner, const bool onLeft)
{
    if (ownerComponent != nullptr)
        ownerComponent->removeComponentListener (this);

    ownerComponent = owner;

    leftOfOwnerComp = onLeft;

    if (ownerComponent != nullptr)
    {
        setVisible (owner->isVisible());
        ownerComponent->addComponentListener (this);
        componentParentHierarchyChanged (*ownerComponent);
        componentMovedOrResized (*ownerComponent, true, true);
    }
}

void NumericLabel::componentMovedOrResized (Component& component, bool /*wasMoved*/, bool /*wasResized*/)
{
    const Font f (getLookAndFeel().getNumericLabelFont (*this));

    if (leftOfOwnerComp)
    {
        setSize (jmin (roundToInt (f.getStringWidthFloat (textValue.toString()) + 0.5f) + getBorderSize().getLeftAndRight(),
                       component.getX()),
                 component.getHeight());

        setTopRightPosition (component.getX(), component.getY());
    }
    else
    {
        setSize (component.getWidth(),
                 getBorderSize().getTopAndBottom() + 6 + roundToInt (f.getHeight() + 0.5f));

        setTopLeftPosition (component.getX(), component.getY() - getHeight());
    }
}

void NumericLabel::componentParentHierarchyChanged (Component& component)
{
    if (Component* parent = component.getParentComponent())
        parent->addChildComponent (this);
}

void NumericLabel::componentVisibilityChanged (Component& component)
{
    setVisible (component.isVisible());
}

//==============================================================================
void NumericLabel::textWasEdited() {}
void NumericLabel::textWasChanged() {}

void NumericLabel::editorShown (TextEditor* textEditor)
{
    Component::BailOutChecker checker (this);
    listeners.callChecked (checker, &NumericLabelListener::editorShown, this, *textEditor);
}

void NumericLabel::editorAboutToBeHidden (TextEditor* textEditor)
{
    if (ComponentPeer* const peer = getPeer())
        peer->dismissPendingTextInput();

    Component::BailOutChecker checker (this);
    listeners.callChecked (checker, &NumericLabelListener::editorHidden, this, *textEditor);
}

void NumericLabel::showEditor()
{
    if (editor == nullptr)
    {
        addAndMakeVisible (editor = createEditorComponent());
        editor->setText(fullTextValue == String::empty ? getText() : fullTextValue, false); // display fulltext only if set
        editor->setKeyboardType (keyboardType);
        editor->addListener (this);
        editor->grabKeyboardFocus();

		if (editor == nullptr) // may be deleted by a callback
            return;

// BEGIN_MODIFIED_BY_RESOLUME
		int length = fullTextValue.length() > 0 ? fullTextValue.length() : textValue.toString().length();
		editor->setHighlightedRegion (Range<int> (0, length));
		//editor->setHighlightedRegion (Range<int> (0, textValue.toString().length()));
// END_MODIFIED_BY_RESOLUME

        resized();
        repaint();

        editorShown (editor);

        enterModalState (false);
        editor->grabKeyboardFocus();
    }
}

bool NumericLabel::updateFromTextEditorContents (TextEditor& ed)
{
    const String newText (ed.getText());
	
// BEGIN_MODIFIED_BY_RESOLUME
    if (textValue.toString() != newText || textValue.toString() != fullTextValue)
    {
		fullTextValue = newText;
	// END_MODIFIED_BY_RESOLUME
        lastTextValue = newText;
        textValue = newText;
        repaint();

        textWasChanged();

        if (ownerComponent != nullptr)
            componentMovedOrResized (*ownerComponent, true, true);

        return true;
    }

    return false;
}

void NumericLabel::hideEditor (const bool discardCurrentEditorContents)
{
    if (editor != nullptr)
    {
        WeakReference<Component> deletionChecker (this);

        ScopedPointer<TextEditor> outgoingEditor (editor);

        editorAboutToBeHidden (outgoingEditor);

        const bool changed = (! discardCurrentEditorContents)
                               && updateFromTextEditorContents (*outgoingEditor);
        outgoingEditor = nullptr;
        repaint();

        if (changed)
            textWasEdited();

        if (deletionChecker != nullptr)
            exitModalState (0);

        if (changed && deletionChecker != nullptr)
            callChangeListeners();
    }
}

void NumericLabel::inputAttemptWhenModal()
{
    if (editor != nullptr)
    {
        if (lossOfFocusDiscardsChanges)
            textEditorEscapeKeyPressed (*editor);
        else
            textEditorReturnKeyPressed (*editor);
    }
}

bool NumericLabel::isBeingEdited() const noexcept
{
    return editor != nullptr;
}

static void copyColourIfSpecified (NumericLabel& l, TextEditor& ed, int colourID, int targetColourID)
{
    if (l.isColourSpecified (colourID) || l.getLookAndFeel().isColourSpecified (colourID))
        ed.setColour (targetColourID, l.findColour (colourID));
}

TextEditor* NumericLabel::createEditorComponent()
{
    TextEditor* const ed = new TextEditor (getName());
    ed->applyFontToAllText (getLookAndFeel().getNumericLabelFont (*this));
    copyAllExplicitColoursTo (*ed);

    copyColourIfSpecified (*this, *ed, textWhenEditingColourId, TextEditor::textColourId);
    copyColourIfSpecified (*this, *ed, backgroundWhenEditingColourId, TextEditor::backgroundColourId);
    copyColourIfSpecified (*this, *ed, outlineWhenEditingColourId, TextEditor::focusedOutlineColourId);

    return ed;
}

TextEditor* NumericLabel::getCurrentTextEditor() const noexcept
{
    return editor;
}

//==============================================================================
void NumericLabel::paint (Graphics& g)
{
    getLookAndFeel().drawNumericLabel (g, *this);
}

void NumericLabel::mouseUp (const MouseEvent& e)
{
    if (editSingleClick
         && isEnabled()
         && contains (e.getPosition())
         && ! (e.mouseWasDraggedSinceMouseDown() || e.mods.isPopupMenu()))
    {
        showEditor();
    }
}

void NumericLabel::mouseDoubleClick (const MouseEvent& e)
{
    if (editDoubleClick
         && isEnabled()
         && ! e.mods.isPopupMenu())
        showEditor();
}

void NumericLabel::resized()
{
    if (editor != nullptr)
        editor->setBounds (getLocalBounds());
}

void NumericLabel::focusGained (FocusChangeType cause)
{
    if (editSingleClick
         && isEnabled()
         && cause == focusChangedByTabKey)
        showEditor();
}

void NumericLabel::enablementChanged()
{
    repaint();
}

void NumericLabel::colourChanged()
{
    repaint();
}

void NumericLabel::setMinimumHorizontalScale (const float newScale)
{
    if (minimumHorizontalScale != newScale)
    {
        minimumHorizontalScale = newScale;
        repaint();
    }
}

//==============================================================================
// We'll use a custom focus traverser here to make sure focus goes from the
// text editor to another component rather than back to the label itself.
class NumericLabelKeyboardFocusTraverser   : public KeyboardFocusTraverser
{
public:
    NumericLabelKeyboardFocusTraverser() {}

    Component* getNextComponent (Component* c)     { return KeyboardFocusTraverser::getNextComponent (getComp (c)); }
    Component* getPreviousComponent (Component* c) { return KeyboardFocusTraverser::getPreviousComponent (getComp (c)); }

    static Component* getComp (Component* current)
    {
        return dynamic_cast<TextEditor*> (current) != nullptr
                 ? current->getParentComponent() : current;
    }
};

KeyboardFocusTraverser* NumericLabel::createFocusTraverser()
{
    return new NumericLabelKeyboardFocusTraverser();
}

//==============================================================================
void NumericLabel::addListener (NumericLabelListener* const listener)
{
    listeners.add (listener);
}

void NumericLabel::removeListener (NumericLabelListener* const listener)
{
    listeners.remove (listener);
}

void NumericLabel::callChangeListeners()
{
    Component::BailOutChecker checker (this);
    listeners.callChecked (checker, &NumericLabelListener::labelTextChanged, this);  // (can't use NumericLabel::Listener due to idiotic VC2005 bug)
}

//==============================================================================
void NumericLabel::textEditorTextChanged (TextEditor& ed)
{
    if (editor != nullptr)
    {
        jassert (&ed == editor);

        if (! (hasKeyboardFocus (true) || isCurrentlyBlockedByAnotherModalComponent()))
        {
            if (lossOfFocusDiscardsChanges)
                textEditorEscapeKeyPressed (ed);
            else
                textEditorReturnKeyPressed (ed);
        }
    }
}

void NumericLabel::textEditorReturnKeyPressed (TextEditor& ed)
{
    if (editor != nullptr)
    {
        jassert (&ed == editor);

        const bool changed = updateFromTextEditorContents (ed);
        hideEditor (true);

        if (changed)
        {
            WeakReference<Component> deletionChecker (this);
            textWasEdited();

            if (deletionChecker != nullptr)
                callChangeListeners();
        }
    }
}

void NumericLabel::textEditorEscapeKeyPressed (TextEditor& ed)
{
    if (editor != nullptr)
    {
        jassert (&ed == editor);
        ignoreUnused (ed);

        editor->setText (textValue.toString(), false);
        hideEditor (true);
    }
}

void NumericLabel::textEditorFocusLost (TextEditor& ed)
{
    textEditorTextChanged (ed);
}
