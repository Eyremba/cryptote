// -*- C++ -*- generated by wxGlade 0.6.2 on Fri Feb 15 21:27:17 2008
// $Id$

#include "wgenpass.h"

// begin wxGlade: ::extracode
// end wxGlade

WGeneratePassword::WGeneratePassword(wxWindow* parent, bool _standalone, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style))
    : wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTHICK_FRAME),
      standalone(_standalone)
{
    // begin wxGlade: WGeneratePassword::WGeneratePassword
    sizer2_staticbox = new wxStaticBox(this, -1, _("Generator Options"));
    const wxString *choicePreset_choices = NULL;
    choicePreset = new wxChoice(this, myID_PRESET, wxDefaultPosition, wxDefaultSize, 0, choicePreset_choices, 0);
    const wxString *choiceType_choices = NULL;
    choiceType = new wxChoice(this, myID_TYPE, wxDefaultPosition, wxDefaultSize, 0, choiceType_choices, 0);
    checkboxSkipSimilarChars = new wxCheckBox(this, myID_SKIPSIMILARCHARS, _("Don't use 0/O and 1/l."));
    checkboxSkipSwappedChars = new wxCheckBox(this, myID_SKIPSWAPPEDCHARS, _("Don't use z/y."));
    spinctrlLength = new wxSpinCtrl(this, myID_LENGTH, wxT("12"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 6, 100);
    textctrlStrength = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    checkboxEnumerate = new wxCheckBox(this, wxID_ANY, _("Enumerate Passwords"));
    buttonRegenerate = new wxButton(this, myID_REGENERATE, _("&Regenerate"));
    listctrlPasslist = new wxListCtrl(this, myID_PASSLIST, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SINGLE_SEL|wxSUNKEN_BORDER);
    textctrlPasslist = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
    buttonOK = new wxButton(this, wxID_OK, wxEmptyString);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    buttonClose = new wxButton(this, wxID_CLOSE, wxEmptyString);
    buttonAbout = new wxButton(this, wxID_ABOUT, _("&About"));

    set_properties();
    do_layout();
    // end wxGlade
}

void WGeneratePassword::set_properties()
{
    // begin wxGlade: WGeneratePassword::set_properties
    SetTitle(_("Password Generator"));
    SetSize(wxSize(400, 600));
    choicePreset->SetToolTip(_("Default or saved password presets."));
    choiceType->SetToolTip(_("Select the components you wish to include in the password."));
    checkboxSkipSimilarChars->SetToolTip(_("Does not include similar, badly recognizable characters in password."));
    checkboxSkipSwappedChars->SetToolTip(_("Does not include characters in password which are swapped on some keyboards."));
    spinctrlLength->SetToolTip(_("Password length desired."));
    textctrlStrength->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    textctrlStrength->SetToolTip(_("Theoretic number of keybits the entropy of the selected pass type generates."));
    checkboxEnumerate->SetToolTip(_("Add serial enumeration to each password line."));
    listctrlPasslist->SetFont(wxFont(10, wxMODERN, wxNORMAL, wxNORMAL, 0, wxT("")));
    textctrlPasslist->SetFont(wxFont(10, wxMODERN, wxNORMAL, wxNORMAL, 0, wxT("")));
    // end wxGlade
}

void WGeneratePassword::do_layout()
{
    // begin wxGlade: WGeneratePassword::do_layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxGridSizer* sizer5 = new wxGridSizer(1, 2, 0, 0);
    wxGridSizer* sizer4 = new wxGridSizer(1, 2, 0, 0);
    wxStaticBoxSizer* sizer2 = new wxStaticBoxSizer(sizer2_staticbox, wxVERTICAL);
    wxFlexGridSizer* sizer3 = new wxFlexGridSizer(7, 2, 0, 0);
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, _("Preset:"));
    sizer3->Add(label1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(choicePreset, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    wxStaticText* label2 = new wxStaticText(this, wxID_ANY, _("Type:"));
    sizer3->Add(label2, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(choiceType, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(5, 5, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(checkboxSkipSimilarChars, 0, wxLEFT|wxRIGHT|wxBOTTOM, 6);
    sizer3->Add(5, 5, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(checkboxSkipSwappedChars, 0, wxLEFT|wxRIGHT|wxBOTTOM, 6);
    wxStaticText* label3 = new wxStaticText(this, wxID_ANY, _("Length:"));
    sizer3->Add(label3, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(spinctrlLength, 0, wxLEFT|wxRIGHT|wxBOTTOM, 6);
    wxStaticText* label4 = new wxStaticText(this, wxID_ANY, _("Theoretic Strength:"));
    sizer3->Add(label4, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(textctrlStrength, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(5, 5, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer3->Add(checkboxEnumerate, 0, wxLEFT|wxRIGHT|wxBOTTOM, 6);
    sizer3->AddGrowableCol(1);
    sizer2->Add(sizer3, 1, wxEXPAND, 0);
    sizer2->Add(buttonRegenerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer2, 0, wxALL|wxEXPAND, 8);
    wxStaticLine* staticline1 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline1, 0, wxEXPAND, 0);
    sizer1->Add(listctrlPasslist, 1, wxALL|wxEXPAND, 8);
    sizer1->Add(textctrlPasslist, 1, wxALL|wxEXPAND, 8);
    wxStaticLine* staticline2 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline2, 0, wxEXPAND, 0);
    sizer4->Add(buttonOK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer4->Add(buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer4, 0, wxEXPAND, 0);
    sizer5->Add(buttonClose, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer5->Add(buttonAbout, 0, wxALL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer5, 0, wxEXPAND, 0);
    SetSizer(sizer1);
    Layout();
    Centre();
    // end wxGlade

    if (standalone)
    {
	sizer1->Hide(listctrlPasslist);
	sizer1->Hide(sizer4);
    }
    else
    {
	sizer3->Hide(12);
	sizer3->Hide(13);
	sizer1->Hide(textctrlPasslist);
	sizer1->Hide(sizer5);
    }
}

BEGIN_EVENT_TABLE(WGeneratePassword, wxDialog)
    // begin wxGlade: WGeneratePassword::event_table
    EVT_CHOICE(myID_PRESET, WGeneratePassword::OnChoicePreset)
    EVT_CHOICE(myID_TYPE, WGeneratePassword::OnChoiceType)
    EVT_CHECKBOX(myID_SKIPSIMILARCHARS, WGeneratePassword::OnCheckSkipSimilarChars)
    EVT_CHECKBOX(myID_SKIPSWAPPEDCHARS, WGeneratePassword::OnCheckSkipSwappedChars)
    EVT_SPINCTRL(myID_LENGTH, WGeneratePassword::OnSpinLength)
    EVT_BUTTON(myID_REGENERATE, WGeneratePassword::OnButtonRegenerate)
    EVT_LIST_ITEM_DESELECTED(myID_PASSLIST, WGeneratePassword::OnPasslistSelected)
    EVT_LIST_ITEM_SELECTED(myID_PASSLIST, WGeneratePassword::OnPasslistSelected)
    EVT_LIST_ITEM_ACTIVATED(myID_PASSLIST, WGeneratePassword::OnPasslistActivated)
    EVT_BUTTON(wxID_OK, WGeneratePassword::OnButtonOK)
    EVT_BUTTON(wxID_CANCEL, WGeneratePassword::OnButtonCancel)
    EVT_BUTTON(wxID_CLOSE, WGeneratePassword::OnButtonClose)
    EVT_BUTTON(wxID_ABOUT, WGeneratePassword::OnButtonAbout)
    // end wxGlade
    EVT_CLOSE(WGeneratePassword::OnClose)
END_EVENT_TABLE();

void WGeneratePassword::OnClose(wxCloseEvent& WXUNUSED(event))
{
    if (standalone)
    {
	Destroy();
    }
    else
    {
	EndModal(wxID_CANCEL);
    }
}

void WGeneratePassword::OnChoicePreset(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnChoicePreset) not implemented yet"));
}

void WGeneratePassword::OnChoiceType(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnChoiceType) not implemented yet"));
}

void WGeneratePassword::OnCheckSkipSimilarChars(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnCheckSkipSimilarChars) not implemented yet"));
}

void WGeneratePassword::OnCheckSkipSwappedChars(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnCheckSkipSwappedChars) not implemented yet"));
}

void WGeneratePassword::OnSpinLength(wxSpinEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnSpinLength) not implemented yet"));
}

void WGeneratePassword::OnButtonRegenerate(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnButtonRegenerate) not implemented yet"));
}

void WGeneratePassword::OnPasslistSelected(wxListEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnPasslistSelected) not implemented yet"));
}

void WGeneratePassword::OnPasslistActivated(wxListEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnPasslistActivated) not implemented yet"));
}

void WGeneratePassword::OnButtonOK(wxCommandEvent& WXUNUSED(event))
{
    EndModal(wxID_OK);
}

void WGeneratePassword::OnButtonCancel(wxCommandEvent& WXUNUSED(event))
{
    EndModal(wxID_CANCEL);
}

void WGeneratePassword::OnButtonClose(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void WGeneratePassword::OnButtonAbout(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnButtonAbout) not implemented yet"));
}

// wxGlade: add WGeneratePassword event handlers
