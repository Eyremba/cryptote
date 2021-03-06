/*******************************************************************************
 * src/pwgen/wpassgen.h
 *
 * Part of CryptoTE, see http://panthema.net/2007/cryptote
 *******************************************************************************
 * Copyright (C) 2008-2014 Timo Bingmann <tb@panthema.net>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 ******************************************************************************/

#ifndef CRYPTOTE_PWGEN_WPASSGEN_HEADER
#define CRYPTOTE_PWGEN_WPASSGEN_HEADER

#include <wx/hyperlink.h>
#include <wx/image.h>
#include <wx/wx.h>

// begin wxGlade: ::dependencies
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
// end wxGlade

#include <vector>

// begin wxGlade: ::extracode
// end wxGlade

class WPassGen : public wxDialog
{
public:
    // begin wxGlade: WPassGen::ids
    enum {
        myID_PRESET = wxID_HIGHEST + 1000,
        myID_PRESET_ADD = wxID_HIGHEST + 1002,
        myID_PRESET_REMOVE = wxID_HIGHEST + 1004,
        myID_TYPE = wxID_HIGHEST + 1006,
        myID_SKIPSIMILARCHAR = wxID_HIGHEST + 1008,
        myID_SKIPSWAPPEDCHAR = wxID_HIGHEST + 1010,
        myID_TEXT_EXTRACHAR = wxID_HIGHEST + 1012,
        myID_LENGTH = wxID_HIGHEST + 1014,
        myID_NUMBER = wxID_HIGHEST + 1016,
        myID_ENUMERATE = wxID_HIGHEST + 1018,
        myID_GENERATE = wxID_HIGHEST + 1020,
        myID_PASSLIST = wxID_HIGHEST + 1022
    };
    // end wxGlade

    WPassGen(wxWindow* parent, bool standalone, int id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

    /// Set if running as stand-alone program: show passwords in text control.
    bool standalone;

    /// Password generator types
    enum pass_type {
        PT_ALPHANUMERICSYMBOL,
        PT_ALPHANUMERIC,
        PT_ALPHA,
        PT_ALPHALOWER,
        PT_PRONOUNCEABLE,
        PT_ALPHAUPPER,
        PT_HEXADECIMAL,
        PT_NUMERIC,
        PT_PORTNUMBER,
        PT_LAST = PT_PORTNUMBER
    };

    // *** Preset Management ***

    struct Preset
    {
        wxString  name;
        pass_type type;
        bool      skip_similar;
        bool      skip_swapped;
        wxString  extrachar;
        int       length;

        // Default Constructor
        Preset() { }

        // Initializing Constructor
        Preset(const wxString& _name, pass_type _type,
               bool _skip_similar, bool _skip_swapped,
               const wxString& _extrachar, int _length)
            : name(_name), type(_type),
              skip_similar(_skip_similar), skip_swapped(_skip_swapped),
              extrachar(_extrachar),
              length(_length)
        { }

        bool operator == (const Preset& o) const
        {
            return (name == o.name)
                   && (type == o.type)
                   && (skip_similar == o.skip_similar)
                   && (skip_swapped == o.skip_swapped)
                   && (extrachar == o.extrachar)
                   && (length == o.length);
        }
    };

    typedef std::vector<Preset> presetlist_type;

    /// List of all password presets
    std::vector<Preset> presetlist;

public:
    /// Return passwords selected by the user
    wxArrayString GetSelectedPassword() const;

    /// Load a list of default password presets when none are defined in the
    /// config file.
    static const std::vector<Preset> & GetDefaultPresets();

    /// Load default settings for all dialog elements
    void LoadDefaultSettings();

    /// Load current settings from config file/registry
    void LoadSettings(class wxConfigBase* cfg);

    /// Save current settings to config file/registry
    void SaveSettings(class wxConfigBase* cfg);

protected:
    // *** Helper Functions ***

    /// Search for a matching preset and set the wxChoice selection.
    void ResetPresetChoice();

    /// Update the keybits text control
    void UpdateKeyStrength();

    /// Update disable/enable status of the check boxes
    void UpdateCheckboxes();

    /// (Re)Generate Password list
    void GenerateList();

    /// Return true if the options skip similar characters is available with
    /// the selected generator type.
    bool IsAllowedSimilar() const;

    /// Return true if the options skip swapped characters is available with
    /// the selected generator type.
    bool IsAllowedSwapped() const;

    /// Return true if the selected generator type supports extra characters.
    bool IsAllowedExtraChar() const;

    /// Return true if the spinctrl length is available with the selected
    /// generator type.
    bool IsAllowedLength() const;

public:
    // *** Static Password Generator Functions ***

    /// Return ASCII Name for password generator type
    static const wxString GetTypeName(pass_type pt);

    /// Return array of possible letters in simple random password.
    static const wxChar * GetType0Letters(pass_type pt, bool skip_similar, bool skip_swapped);

    /// Return array of possible letters in simple random password plus extra characters
    static wxString GetType0LettersExtra(const Preset& preset);

    /// Make one password of the generic random sequence type.
    static wxString MakePasswordType0(unsigned int len, const wxString& letters);

    /// Return keybits per letter for currently selected generator type;
    static float GetTypeKeybits(const Preset& preset);

    /// Make one password of the given Preset type
    static wxString MakePassword(const Preset& preset);

private:
    // begin wxGlade: WPassGen::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: WPassGen::attributes
    wxStaticBox* sizer2_staticbox;
    wxChoice* choicePreset;
    wxBitmapButton* buttonPresetAdd;
    wxBitmapButton* buttonPresetRemove;
    wxChoice* choiceType;
    wxCheckBox* checkboxSkipSimilarChar;
    wxCheckBox* checkboxSkipSwappedChar;
    wxTextCtrl* textctrlExtraChar;
    wxSpinCtrl* spinctrlLength;
    wxTextCtrl* textctrlStrength;
    wxSpinCtrl* spinctrlNumber;
    wxCheckBox* checkboxEnumerate;
    wxButton* buttonGenerate;
    wxListCtrl* listctrlPasslist;
    wxTextCtrl* textctrlPasslist;
    wxButton* buttonOK;
    wxButton* buttonCancel;
    wxButton* buttonAbout;
    wxButton* buttonClose;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    void OnClose(wxCloseEvent& event);
    void OnChoicePreset(wxCommandEvent& event);         // wxGlade: <event_handler>
    void OnChoiceType(wxCommandEvent& event);           // wxGlade: <event_handler>
    void OnCheckSkipSimilarChar(wxCommandEvent& event); // wxGlade: <event_handler>
    void OnCheckSkipSwappedChar(wxCommandEvent& event); // wxGlade: <event_handler>
    void OnTextExtraCharChange(wxCommandEvent& event);  // wxGlade: <event_handler>
    void OnSpinLength(wxSpinEvent& event);              // wxGlade: <event_handler>
    void OnSpinNumber(wxSpinEvent& event);              // wxGlade: <event_handler>
    void OnCheckEnumerate(wxCommandEvent& event);       // wxGlade: <event_handler>
    void OnButtonGenerate(wxCommandEvent& event);       // wxGlade: <event_handler>
    void OnPasslistSelected(wxListEvent& event);        // wxGlade: <event_handler>
    void OnPasslistActivated(wxListEvent& event);       // wxGlade: <event_handler>
    void OnButtonOK(wxCommandEvent& event);             // wxGlade: <event_handler>
    void OnButtonCancel(wxCommandEvent& event);         // wxGlade: <event_handler>
    void OnButtonClose(wxCommandEvent& event);          // wxGlade: <event_handler>
    void OnButtonAbout(wxCommandEvent& event);          // wxGlade: <event_handler>
    void OnButtonPresetAdd(wxCommandEvent& event);      // wxGlade: <event_handler>
    void OnButtonPresetRemove(wxCommandEvent& event);   // wxGlade: <event_handler>
};                                                      // wxGlade: end class

class PGWAbout : public wxDialog
{
public:
    // begin wxGlade: PGWAbout::ids
    // end wxGlade

    PGWAbout(wxWindow* parent, int id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: PGWAbout::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: PGWAbout::attributes
    wxStaticBitmap* bitmapIcon;
    wxStaticBitmap* bitmapWeb;
    wxHyperlinkCtrl* hyperlink1;
    wxButton* buttonOK;
    // end wxGlade
}; // wxGlade: end class

#endif // !CRYPTOTE_PWGEN_WPASSGEN_HEADER

/******************************************************************************/
