// -*- C++ -*- generated by wxGlade 0.6.2 on Fri Feb 15 21:27:17 2008
// $Id$

#include "wgenpass.h"
#include "tools.h"
#include "prng.h"
#include "fips181.h"

#include <wx/config.h>
#include <wx/textdlg.h>

// begin wxGlade: ::extracode
// end wxGlade

WGeneratePassword::WGeneratePassword(wxWindow* parent, bool _standalone, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style))
    : wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTHICK_FRAME),
      standalone(_standalone)
{
    {
	#include "art/pwgen-16.h"
	#include "art/pwgen-22.h"
	#include "art/pwgen-32.h"
	#include "art/pwgen-48.h"

	wxIconBundle progicon;

	progicon.AddIcon( wxIconFromMemory(pwgen_16_png) );
	progicon.AddIcon( wxIconFromMemory(pwgen_22_png) );
	progicon.AddIcon( wxIconFromMemory(pwgen_32_png) );
	progicon.AddIcon( wxIconFromMemory(pwgen_48_png) );

	SetIcons(progicon);
    }

    // begin wxGlade: WGeneratePassword::WGeneratePassword
    sizer2_staticbox = new wxStaticBox(this, -1, _("Generator Options"));
    const wxString *choicePreset_choices = NULL;
    choicePreset = new wxChoice(this, myID_PRESET, wxDefaultPosition, wxDefaultSize, 0, choicePreset_choices, 0);
    buttonPresetAdd = new wxBitmapButton(this, myID_PRESET_ADD, wxNullBitmap);
    buttonPresetRemove = new wxBitmapButton(this, myID_PRESET_REMOVE, wxNullBitmap);
    const wxString *choiceType_choices = NULL;
    choiceType = new wxChoice(this, myID_TYPE, wxDefaultPosition, wxDefaultSize, 0, choiceType_choices, 0);
    checkboxSkipSimilarChars = new wxCheckBox(this, myID_SKIPSIMILARCHARS, _("Don't use 0/O and 1/l."));
    checkboxSkipSwappedChars = new wxCheckBox(this, myID_SKIPSWAPPEDCHARS, _("Don't use z/y."));
    spinctrlLength = new wxSpinCtrl(this, myID_LENGTH, wxT("12"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 6, 100);
    textctrlStrength = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    checkboxEnumerate = new wxCheckBox(this, myID_ENUMERATE, _("Enumerate Passwords"));
    buttonGenerate = new wxButton(this, myID_GENERATE, _("&Generate"));
    listctrlPasslist = new wxListCtrl(this, myID_PASSLIST, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SINGLE_SEL|wxSUNKEN_BORDER);
    textctrlPasslist = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
    buttonOK = new wxButton(this, wxID_OK, wxEmptyString);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    buttonClose = new wxButton(this, wxID_CLOSE, wxEmptyString);
    buttonAbout = new wxButton(this, wxID_ABOUT, _("&About"));

    set_properties();
    do_layout();
    // end wxGlade

    // set bitmap from compiled-in PNGs
    {
	#include "art/edit_add.h"
	#include "art/edit_remove.h"

	buttonPresetAdd->SetBitmapLabel( wxBitmapFromMemory(edit_add_png) );
	buttonPresetRemove->SetBitmapLabel( wxBitmapFromMemory(edit_remove_png) );
    }

    // insert password type names
    for (unsigned int pt = 0; pt <= PT_LAST; ++pt)
    {
	choiceType->Append( GetTypeName((pass_type)pt) );
    }

    // load settings from wxConfig
    {
	wxConfigBase* cfg = wxConfigBase::Get();

	cfg->SetPath(_T("/pwgen"));

	int preset, type, length;
	bool skipsimilar, skipswapped, enumerate;

	cfg->Read(_T("preset"), &preset, 0);
	cfg->Read(_T("type"), &type, 0);
	cfg->Read(_T("skipsimilar"), &skipsimilar, false);
	cfg->Read(_T("skipswapped"), &skipswapped, false);
	cfg->Read(_T("length"), &length, 12);
	cfg->Read(_T("enumerate"), &enumerate, false);

	choicePreset->SetSelection(preset);
	choiceType->SetSelection(type);
	checkboxSkipSimilarChars->SetValue(skipsimilar);
	checkboxSkipSwappedChars->SetValue(skipswapped);
	spinctrlLength->SetValue(length);
	checkboxEnumerate->SetValue(enumerate);

	cfg->SetPath(_T("/pwgen/presets"));

	for (unsigned int pi = 0; cfg->HasGroup(wxString::Format(_T("%d"), pi)) ; ++pi)
	{
	    cfg->SetPath( wxString::Format(_T("%d"), pi) );

	    Preset preset;

	    cfg->Read(_T("name"), &preset.name, _("<unknown>"));
	    cfg->Read(_T("type"), &preset.type, 0);
	    cfg->Read(_T("skipsimilar"), &preset.skipsimilar, false);
	    cfg->Read(_T("skipswapped"), &preset.skipswapped, false);
	    cfg->Read(_T("length"), &preset.length, 12);
	    cfg->Read(_T("enumerate"), &preset.enumerate, false);

	    presetlist.push_back(preset);

	    cfg->SetPath(_T(".."));
	}
    }

    // update dialog logic
    ResetPresetChoice();
    UpdateCheckboxes();
    UpdateKeyStrength();
    GenerateList();

    buttonOK->Disable();
}

void WGeneratePassword::set_properties()
{
    // begin wxGlade: WGeneratePassword::set_properties
    SetTitle(_("Password Generator"));
    SetSize(wxSize(400, 600));
    choicePreset->SetToolTip(_("Default or saved password presets."));
    buttonPresetAdd->SetToolTip(_("Save the current settings as a new preset."));
    buttonPresetAdd->SetSize(buttonPresetAdd->GetBestSize());
    buttonPresetRemove->SetToolTip(_("Remove current preset."));
    buttonPresetRemove->SetSize(buttonPresetRemove->GetBestSize());
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
    wxGridSizer* sizer6 = new wxGridSizer(1, 2, 0, 0);
    wxGridSizer* sizer5 = new wxGridSizer(1, 2, 0, 0);
    wxStaticBoxSizer* sizer2 = new wxStaticBoxSizer(sizer2_staticbox, wxVERTICAL);
    wxFlexGridSizer* sizer3 = new wxFlexGridSizer(7, 2, 0, 0);
    wxBoxSizer* sizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, _("Preset:"));
    sizer3->Add(label1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer4->Add(choicePreset, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    sizer4->Add(buttonPresetAdd, 0, wxLEFT, 6);
    sizer4->Add(buttonPresetRemove, 0, wxLEFT, 6);
    sizer3->Add(sizer4, 1, wxALL|wxEXPAND, 6);
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
    sizer2->Add(buttonGenerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer2, 0, wxALL|wxEXPAND, 8);
    wxStaticLine* staticline1 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline1, 0, wxEXPAND, 0);
    sizer1->Add(listctrlPasslist, 1, wxALL|wxEXPAND, 8);
    sizer1->Add(textctrlPasslist, 1, wxALL|wxEXPAND, 8);
    wxStaticLine* staticline2 = new wxStaticLine(this, wxID_ANY);
    sizer1->Add(staticline2, 0, wxEXPAND, 0);
    sizer5->Add(buttonOK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer5->Add(buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer5, 0, wxEXPAND, 0);
    sizer6->Add(buttonClose, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 6);
    sizer6->Add(buttonAbout, 0, wxALL|wxALIGN_CENTER_VERTICAL, 6);
    sizer1->Add(sizer6, 0, wxEXPAND, 0);
    SetSizer(sizer1);
    Layout();
    Centre();
    // end wxGlade

    if (standalone)
    {
	sizer1->Hide(listctrlPasslist);
	sizer1->Hide(sizer5);
    }
    else
    {
	sizer3->Hide(12);
	sizer3->Hide(13);
	sizer1->Hide(textctrlPasslist);
	sizer1->Hide(sizer6);
    }
}

BEGIN_EVENT_TABLE(WGeneratePassword, wxDialog)
    // begin wxGlade: WGeneratePassword::event_table
    EVT_CHOICE(myID_PRESET, WGeneratePassword::OnChoicePreset)
    EVT_BUTTON(myID_PRESET_ADD, WGeneratePassword::OnButtonPresetAdd)
    EVT_BUTTON(myID_PRESET_REMOVE, WGeneratePassword::OnButtonPresetRemove)
    EVT_CHOICE(myID_TYPE, WGeneratePassword::OnChoiceType)
    EVT_CHECKBOX(myID_SKIPSIMILARCHARS, WGeneratePassword::OnCheckSkipSimilarChars)
    EVT_CHECKBOX(myID_SKIPSWAPPEDCHARS, WGeneratePassword::OnCheckSkipSwappedChars)
    EVT_SPINCTRL(myID_LENGTH, WGeneratePassword::OnSpinLength)
    EVT_CHECKBOX(myID_ENUMERATE, WGeneratePassword::OnCheckEnumerate)
    EVT_BUTTON(myID_GENERATE, WGeneratePassword::OnButtonGenerate)
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

void WGeneratePassword::SaveSettings()
{
    wxConfigBase* cfg = wxConfigBase::Get();

    cfg->SetPath(_T("/pwgen"));

    cfg->Write(_T("preset"), choicePreset->GetSelection());
    cfg->Write(_T("type"), choiceType->GetSelection());
    cfg->Write(_T("skipsimilar"), checkboxSkipSimilarChars->GetValue());
    cfg->Write(_T("skipswapped"), checkboxSkipSwappedChars->GetValue());
    cfg->Write(_T("length"), spinctrlLength->GetValue());
    cfg->Write(_T("enumerate"), checkboxEnumerate->GetValue());

    cfg->DeleteGroup(_T("/pwgen/presets"));
    cfg->SetPath(_T("/pwgen/presets"));

    for (unsigned int pi = 0; pi < presetlist.size(); ++pi)
    {
	cfg->SetPath( wxString::Format(_T("%d"), pi) );

	cfg->Write(_T("name"), presetlist[pi].name);
	cfg->Write(_T("type"), presetlist[pi].type);
	cfg->Write(_T("skipsimilar"), presetlist[pi].skipsimilar);
	cfg->Write(_T("skipswapped"), presetlist[pi].skipswapped);
	cfg->Write(_T("length"), presetlist[pi].length);
	cfg->Write(_T("enumerate"), presetlist[pi].enumerate);

	cfg->SetPath(_T(".."));
    }

    cfg->Flush();
}

void WGeneratePassword::OnClose(wxCloseEvent& WXUNUSED(event))
{
    if (standalone)
    {
	SaveSettings();
	Destroy();
    }
    else
    {
	SaveSettings();
	EndModal(wxID_CANCEL);
    }
}

void WGeneratePassword::OnChoicePreset(wxCommandEvent& WXUNUSED(event))
{
    int ni = choicePreset->GetSelection();

    if (ni < 0 || (unsigned int)ni >= presetlist.size()) return;

    const Preset& preset = presetlist[ni];

    choiceType->SetSelection(preset.type);
    checkboxSkipSimilarChars->SetValue(preset.skipsimilar);
    checkboxSkipSwappedChars->SetValue(preset.skipswapped);
    spinctrlLength->SetValue(preset.length);
    checkboxEnumerate->SetValue(preset.enumerate);
}

void WGeneratePassword::OnButtonPresetAdd(wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog dlg(this, _("Enter a descriptive name for the new preset:"), _("Add New Password Preset"));

    if (dlg.ShowModal() != wxID_OK) return;

    Preset preset;

    preset.name = dlg.GetValue();
    preset.type = choiceType->GetSelection();
    preset.skipsimilar = checkboxSkipSimilarChars->GetValue();
    preset.skipswapped = checkboxSkipSwappedChars->GetValue();
    preset.length = spinctrlLength->GetValue();
    preset.enumerate = checkboxEnumerate->GetValue();

    presetlist.push_back(preset);

    ResetPresetChoice();
}

void WGeneratePassword::OnButtonPresetRemove(wxCommandEvent& WXUNUSED(event))
{
    int ni = choicePreset->GetSelection();

    if (ni < 0 || (unsigned int)ni >= presetlist.size()) return;

    presetlist.erase(presetlist.begin() + ni);

    ResetPresetChoice();
}

void WGeneratePassword::OnChoiceType(wxCommandEvent& WXUNUSED(event))
{
    ResetPresetChoice();
    UpdateCheckboxes();
    UpdateKeyStrength();
}

void WGeneratePassword::OnCheckSkipSimilarChars(wxCommandEvent& WXUNUSED(event))
{
    ResetPresetChoice();
    UpdateKeyStrength();
}

void WGeneratePassword::OnCheckSkipSwappedChars(wxCommandEvent& WXUNUSED(event))
{
    ResetPresetChoice();
    UpdateKeyStrength();
}

void WGeneratePassword::OnSpinLength(wxSpinEvent& WXUNUSED(event))
{
    ResetPresetChoice();
    UpdateKeyStrength();
}

void WGeneratePassword::OnCheckEnumerate(wxCommandEvent& WXUNUSED(event))
{
    ResetPresetChoice();
}

void WGeneratePassword::OnButtonGenerate(wxCommandEvent& WXUNUSED(event))
{
    GenerateList();
}

void WGeneratePassword::OnPasslistSelected(wxListEvent& WXUNUSED(event))
{
    buttonOK->Enable( listctrlPasslist->GetSelectedItemCount() != 0 );
}

void WGeneratePassword::OnPasslistActivated(wxListEvent& event)
{
    OnButtonOK(event);
}

void WGeneratePassword::OnButtonOK(wxCommandEvent& WXUNUSED(event))
{
    SaveSettings();
    EndModal(wxID_OK);
}

void WGeneratePassword::OnButtonCancel(wxCommandEvent& WXUNUSED(event))
{
    SaveSettings();
    EndModal(wxID_CANCEL);
}

void WGeneratePassword::OnButtonClose(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void WGeneratePassword::OnButtonAbout(wxCommandEvent& event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WGeneratePassword::OnButtonAbout) not implemented yet"));
}

// wxGlade: add WGeneratePassword event handlers

void WGeneratePassword::ResetPresetChoice()
{
    choicePreset->Clear();

    for(presetlist_type::const_iterator pi = presetlist.begin();
	pi != presetlist.end(); ++pi)
    {
        int ni = choicePreset->Append(pi->name);

	int passtype = choiceType->GetSelection();
	bool skipsimilar = checkboxSkipSimilarChars->GetValue();
	bool skipswapped = checkboxSkipSwappedChars->GetValue();
	int length = spinctrlLength->GetValue();
	bool enumerate = checkboxEnumerate->GetValue();

	if (pi->type == passtype &&
	    pi->skipsimilar == skipsimilar &&
	    pi->skipswapped == skipswapped &&
	    pi->length == length &&
	    pi->enumerate == enumerate)
	{
	    choicePreset->SetSelection(ni);
	}
    }
}

void WGeneratePassword::UpdateCheckboxes()
{
    checkboxSkipSimilarChars->Enable( IsAllowedSimilar() );
    checkboxSkipSwappedChars->Enable( IsAllowedSwapped() );
    spinctrlLength->Enable( IsAllowedLength() );
}

void WGeneratePassword::UpdateKeyStrength()
{
    int passlen = spinctrlLength->GetValue();

    double keybits = GetTypeKeybits();

    if (IsAllowedLength()) keybits *= passlen;

    wxString ss = wxString::Format(_T("%.1f keybits"), keybits);

    textctrlStrength->SetValue(ss);
}

void WGeneratePassword::GenerateList()
{
    int passlen = spinctrlLength->GetValue();
    bool enumerate = checkboxEnumerate->GetValue();

    if (standalone)
    {
	// Fill wxTextCtrl with password

	wxString text;

	for(unsigned int i = 0; i < 10; i++)
	{
	    if (enumerate)
		text += wxString::Format(_T("%u "), i);

	    text += MakePassword(passlen) + _T("\n");
	}

	textctrlPasslist->SetValue(text);
    }
    else
    {
	// Fill wxListCtrl with password

	listctrlPasslist->DeleteAllItems();

	for(unsigned int i = 0; i < 10; i++)
	{
	    listctrlPasslist->InsertItem(i, MakePassword(passlen) );
	}
    }

    buttonOK->Disable();
}

// *** Password Generator Functions ***

const wxChar* WGeneratePassword::GetTypeName(pass_type pt)
{
    switch(pt)
    {
    case PT_PRONOUNCEABLE:
	return _("Pronounceable Password");

    case PT_ALPHANUMERIC:
	return _("Random Letters + Numbers");

    case PT_ALPHA:
	return _("Random Letters");

    case PT_ALPHALOWER:
	return _("Random Lower-case Letters");

    case PT_ALPHAUPPER:
	return _("Random Upper-case Letters");

    case PT_HEXADECIMAL:
	return _("Random Hexadecimal Number");

    case PT_NUMERIC:
	return _("Random Numbers");

    case PT_PORTNUMBER:
	return _("Random IP Port Number");

    default:
	return _("Unknown");
    }
}

const wxChar* WGeneratePassword::GetType0Letters(pass_type pt, bool skip_similar, bool skip_swapped)
{
    switch(pt)
    {
    case PT_PRONOUNCEABLE:
	assert(0);
	return _T("");

    case PT_ALPHANUMERIC:
    
	if (skip_similar && skip_swapped)
	    return _T("ABCDEFGHIJKLMNPQRSTUVWXabcdefghijkmnopqrstuvwx23456789");
	else if (skip_similar && !skip_swapped)
	    return _T("ABCDEFGHIJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz23456789");
	else if (!skip_similar && skip_swapped)
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWXabcdefghijklmnopqrstuvwx0123456789");
	else
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    case PT_ALPHA:
    
	if (skip_swapped)
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWXabcdefghijklmnopqrstuvwx");
	else
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    case PT_ALPHALOWER:
    
	if (skip_swapped)
	    return _T("abcdefghijklmnopqrstuvwx");
	else
	    return _T("abcdefghijklmnopqrstuvwxyz");

    case PT_ALPHAUPPER:
    
	if (skip_swapped)
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWX");
	else
	    return _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    case PT_HEXADECIMAL:
    
	return _T("0123456789ABCDEF");

    case PT_NUMERIC:

	return _T("0123456789");

    case PT_PORTNUMBER:
	assert(0);
	return _T("");
    }

    return _T("");
}

float WGeneratePassword::GetTypeKeybits() const
{
    pass_type passtype = (pass_type)choiceType->GetSelection();
    bool skip_similar = checkboxSkipSimilarChars->GetValue();
    bool skip_swapped = checkboxSkipSwappedChars->GetValue();

    switch(passtype)
    {
    case PT_PRONOUNCEABLE:
	// The FIPS-181 standard says "Approximately 18 million 6-character,
	// 5.7 billion 8-character, and 1.6 trillion 10-character passwords can
	// be created by the program." This is equivalent to about 4.05 keybits
	// per letter.
	return 4.05;

    case PT_ALPHANUMERIC:
    case PT_ALPHA:
    case PT_ALPHALOWER:
    case PT_ALPHAUPPER:
    case PT_HEXADECIMAL:
    case PT_NUMERIC:
    {
	double letternum = wxStrlen( GetType0Letters(passtype, skip_similar, skip_swapped) );
	return log(letternum) / log(2);
    }

    case PT_PORTNUMBER:
	return log(65536) / log(2);
    }

    return 0;
}

bool WGeneratePassword::IsAllowedSimilar() const
{
    pass_type passtype = (pass_type)choiceType->GetSelection();

    switch(passtype)
    {
    case PT_PRONOUNCEABLE:
	return false;
	
    case PT_ALPHANUMERIC:
	return true;

    case PT_ALPHA:
    case PT_ALPHALOWER:
    case PT_ALPHAUPPER:
	return false;
   
    case PT_HEXADECIMAL:
    case PT_NUMERIC:
    default:
	return false;
    }
}

bool WGeneratePassword::IsAllowedSwapped() const
{
    pass_type passtype = (pass_type)choiceType->GetSelection();

    switch(passtype)
    {
    case PT_PRONOUNCEABLE:
	return false;
	
    case PT_ALPHANUMERIC:
	return true;

    case PT_ALPHA:
    case PT_ALPHALOWER:
    case PT_ALPHAUPPER:
	return true;
   
    case PT_HEXADECIMAL:
    case PT_NUMERIC:
    default:
	return false;
    }
}

bool WGeneratePassword::IsAllowedLength() const
{
    pass_type passtype = (pass_type)choiceType->GetSelection();

    switch(passtype)
    {
    case PT_PRONOUNCEABLE:
    case PT_ALPHANUMERIC:
    case PT_ALPHA:
    case PT_ALPHALOWER:
    case PT_ALPHAUPPER:
    case PT_HEXADECIMAL:
    case PT_NUMERIC:
	return true;

    case PT_PORTNUMBER:
	return false;
   
    default:
	return false;
    }
}

// Use one global random generator instance for password.
static class PRNG randgen;

/// Function with right signature for FIPS181 argument.
static int randgen_func()
{
    return randgen.get_int32();
}

wxString WGeneratePassword::MakePasswordType0(unsigned int len, const wxChar* letters)
{
    wxString s;
    unsigned int lettlen = wxStrlen(letters);

    for(unsigned int i = 0; i < len; ++i)
    {
	s.Append( letters[ randgen.get(lettlen) ] );
    }

    return s;
}

wxString WGeneratePassword::MakePassword(unsigned int passlen)
{
    pass_type passtype = (pass_type)choiceType->GetSelection();
    bool skip_similar = checkboxSkipSimilarChars->GetValue();
    bool skip_swapped = checkboxSkipSwappedChars->GetValue();

    switch(passtype)
    {
    case PT_PRONOUNCEABLE:
    {
	FIPS181 fips181 (randgen_func);

	std::string word, hypenated_word;
	fips181.randomword(word, hypenated_word, passlen, passlen);

	return wxString(word.data(), wxConvUTF8, word.size());
    }

    case PT_ALPHANUMERIC:
    case PT_ALPHA:
    case PT_ALPHALOWER:
    case PT_ALPHAUPPER:
    case PT_HEXADECIMAL:
    case PT_NUMERIC:
    {
	const wxChar* letters = GetType0Letters(passtype, skip_similar, skip_swapped);

	return MakePasswordType0(passlen, letters);
    }

    case PT_PORTNUMBER:
    {
	return wxString::Format(_T("%u"), randgen.get(65536));
    }
    }

    return _T("");
}
