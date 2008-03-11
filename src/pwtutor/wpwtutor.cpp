// -*- C++ -*- generated by wxGlade 0.6.2 on Sun Feb 17 09:28:37 2008
// $Id$

#include "wpwtutor.h"
#include "wnewpass.h"
#include "wquery.h"
#include "wstats.h"

#include "common/tools.h"

#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/tokenzr.h>

#include <stdexcept>
#include <stdint.h>
#include <assert.h>

// begin wxGlade: ::extracode
// end wxGlade

WPWTutor::WPWTutor(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style))
    : wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    {
	#include "art/pwtutor-16.h"
	#include "art/pwtutor-22.h"
	#include "art/pwtutor-32.h"
	#include "art/pwtutor-48.h"

	wxIconBundle progicon;

	progicon.AddIcon( wxIconFromMemory(pwtutor_16_png) );
	progicon.AddIcon( wxIconFromMemory(pwtutor_22_png) );
	progicon.AddIcon( wxIconFromMemory(pwtutor_32_png) );
	progicon.AddIcon( wxIconFromMemory(pwtutor_48_png) );

	SetIcons(progicon);
    }

    // begin wxGlade: WPWTutor::WPWTutor
    sizer2_staticbox = new wxStaticBox(this, -1, _("Learning List"));
    listctrlPasslist = new wxListCtrl(this, myID_PASSLIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxSUNKEN_BORDER);
    buttonNewPass = new wxButton(this, myID_NEWPASS, _("&Learn New Password"));
    buttonAbout = new wxButton(this, myID_ABOUT, _("&About / Config"));
    buttonHide = new wxButton(this, myID_HIDE, _("&Hide"));

    set_properties();
    do_layout();
    // end wxGlade

    // Set up list control for passes
    listctrlPasslist->InsertColumn(0, _("Status"), wxLIST_FORMAT_LEFT, 60);
    listctrlPasslist->InsertColumn(1, _("Description"), wxLIST_FORMAT_LEFT, 100);
    listctrlPasslist->InsertColumn(2, _("Queries / Right / Wrong / Revealed"), wxLIST_FORMAT_LEFT, 100);

    PassImageList = new wxImageList(80, 16);
    listctrlPasslist->AssignImageList(PassImageList, wxIMAGE_LIST_SMALL);

    listctrlPasslist->SetColumnWidth(0, 80+4);
    listctrlPasslist->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    listctrlPasslist->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);

    loadPasslist();

    taskbaricon = new WTaskBarIcon(this);
}

WPWTutor::~WPWTutor()
{
    delete taskbaricon;
}

void WPWTutor::set_properties()
{
    // begin wxGlade: WPWTutor::set_properties
    SetTitle(_("CryptoTE Password Tutor"));
    SetSize(wxSize(400, 300));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    // end wxGlade
}

void WPWTutor::do_layout()
{
    // begin wxGlade: WPWTutor::do_layout
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer2 = new wxStaticBoxSizer(sizer2_staticbox, wxVERTICAL);
    wxStaticText* label1 = new wxStaticText(this, wxID_ANY, _("CryptoTE Password Tutor"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    label1->SetFont(wxFont(18, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));
    sizer1->Add(label1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 6);
    sizer2->Add(listctrlPasslist, 1, wxALL|wxEXPAND, 6);
    sizer2->Add(buttonNewPass, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL, 6);
    sizer1->Add(sizer2, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 6);
    sizer3->Add(buttonAbout, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    sizer3->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizer3->Add(buttonHide, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    sizer1->Add(sizer3, 0, wxALL|wxEXPAND, 4);
    SetSizer(sizer1);
    Layout();
    Centre();
    SetSize(wxSize(400, 300));
    // end wxGlade
}

BEGIN_EVENT_TABLE(WPWTutor, wxFrame)
    // begin wxGlade: WPWTutor::event_table
    EVT_LIST_ITEM_ACTIVATED(myID_PASSLIST, WPWTutor::OnPasslistItemActivated)
    EVT_LIST_ITEM_RIGHT_CLICK(myID_PASSLIST, WPWTutor::OnPasslistItemRightClick)
    EVT_BUTTON(myID_NEWPASS, WPWTutor::OnButtonNewPass)
    EVT_BUTTON(myID_ABOUT, WPWTutor::OnButtonAbout)
    EVT_BUTTON(myID_HIDE, WPWTutor::OnButtonClose)
    // end wxGlade

    EVT_CLOSE(WPWTutor::OnClose)

    EVT_MENU(myID_MENU_STATS, WPWTutor::OnMenuStatistics)
    EVT_MENU(myID_MENU_QUERY, WPWTutor::OnMenuQuery)
    EVT_MENU(myID_MENU_STOP, WPWTutor::OnMenuStop)
    EVT_MENU(myID_MENU_ERASE, WPWTutor::OnMenuErase)
END_EVENT_TABLE();

void WPWTutor::OnPasslistItemActivated(wxListEvent& event)
{
    int ni = event.GetIndex();
    if (ni < 0 || (unsigned int)ni >= passlist.size()) return;

    WPassStats dlg(passlist[ni], this);

    if (dlg.ShowModal() == wxID_OK)
    {
	UpdatePassEntry(ni);
    }
    savePasslist();
}

void WPWTutor::OnPasslistItemRightClick(wxListEvent& event)
{
    int ni = event.GetIndex();
    if (ni < 0 || (unsigned int)ni >= passlist.size()) return;

    wxMenu* menu = new wxMenu;
    menu->Append(myID_MENU_STATS, _("&Show learning statistics."));
    menu->Append(myID_MENU_QUERY, _("&Query for this password now."));
    menu->AppendSeparator();
    menu->Append(myID_MENU_STOP, _("Temporarily s&top asking for this password."));
    menu->Append(myID_MENU_ERASE, _("&Erase this password."));

    PopupMenu(menu);
}

void WPWTutor::OnButtonNewPass(wxCommandEvent& WXUNUSED(event))
{
    WNewPass dlg(this);

    if (dlg.ShowModal() == wxID_OK)
    {
	passlist.push_back(dlg.passentry);
	AppendPassEntry(dlg.passentry);

	savePasslist();
    }
}

void WPWTutor::OnButtonAbout(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (WPWTutor::OnButtonAbout) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}

void WPWTutor::OnButtonClose(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void WPWTutor::OnClose(wxCloseEvent& event)
{
    if (!event.CanVeto())
    {
	Destroy();
    }
    else
    {
	Hide();
	taskbaricon->Install();
    }
}

void WPWTutor::OnMenuStatistics(wxCommandEvent& WXUNUSED(event))
{
    int ni = listctrlPasslist->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (ni < 0 || (unsigned int)ni >= passlist.size()) return;

    WPassStats dlg(passlist[ni], this);

    if (dlg.ShowModal() == wxID_OK)
    {
	UpdatePassEntry(ni);
    }
    savePasslist();
}

void WPWTutor::OnMenuQuery(wxCommandEvent& WXUNUSED(event))
{
    int ni = listctrlPasslist->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (ni < 0 || (unsigned int)ni >= passlist.size()) return;

    WQueryPass dlg(passlist[ni], this);

    if (dlg.ShowModal() == wxID_OK)
    {
	UpdatePassEntry(ni);
    }
    savePasslist();
}

void WPWTutor::OnMenuStop(wxCommandEvent& WXUNUSED(event))
{

}

void WPWTutor::OnMenuErase(wxCommandEvent& WXUNUSED(event))
{
    int ni = listctrlPasslist->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (ni < 0 || (unsigned int)ni >= passlist.size()) return;

    passlist.erase(passlist.begin() + ni);
    savePasslist();

    listctrlPasslist->DeleteItem(ni);
    PassImageList->Remove(ni); // TODO: this does not work.
}

// wxGlade: add WPWTutor event handlers

// *** PassEntry Management Functions ***

void WPWTutor::AppendPassEntry(struct PassEntry& WXUNUSED(pe))
{
    int ni = listctrlPasslist->GetItemCount();

    ni = listctrlPasslist->InsertItem(ni, _T(""));

    UpdatePassEntry(ni);
}

void WPWTutor::UpdatePassEntry(int ni)
{
    struct PassEntry& pe = passlist[ni];

    UpdatePassImageList(ni);

    listctrlPasslist->SetItemColumnImage(ni, 0, ni);
    listctrlPasslist->SetItem(ni, 1, pe.description);
    listctrlPasslist->SetItem(ni, 2, wxString::Format(_("%d / %d / %d / %d"), pe.scores.size(), pe.rights, pe.wrongs, pe.revealed) );
}

void WPWTutor::UpdatePassImageList(int ni)
{
    wxBitmap bmp = MakeScoreBitmap(passlist[ni]);

    if (PassImageList->GetImageCount() <= ni)
    {
	assert(PassImageList->GetImageCount() == ni);
	PassImageList->Add(bmp);
    }
    else {
	PassImageList->Replace(ni, bmp);
    }

    listctrlPasslist->Refresh();
}

wxBitmap WPWTutor::MakeScoreBitmap(const PassEntry& passentry)
{
    const int height = 16;
    const int width = 80;

    wxBitmap bitmap(width, height);
    wxMemoryDC dc;
    dc.SelectObject(bitmap);

    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    double step = (double)(width-2) / std::min<double>(passentry.scores.size(), 6);

    // support points in gradient

    static const struct GradientPoint gradient[] =
	{
	    {   0, wxColour(  0, 242, 0) },
	    {   1, wxColour(194, 242, 0) },
	    {  10, wxColour(242, 214, 0) },
	    {  40, wxColour(242,   0, 0) }
	};

    for(unsigned int i = 0; i < passentry.scores.size() && i < 6; ++i)
    {
	const int& score = passentry.scores[ passentry.scores.size() - 1 - i ];

	wxColour colour = InterpolateGradient(score, gradient, sizeof(gradient) / sizeof(gradient[0]));

	dc.SetBrush( wxBrush(colour) );
	dc.SetPen(*wxTRANSPARENT_PEN);

	int rectw = wxCoord(step)+1;
	if (i+1 == passentry.scores.size() || i == 5) rectw = width-2 - wxCoord(i*step);

	dc.DrawRectangle( 1+wxCoord(i*step), 1, rectw, height-2);
    }

    return bitmap;
}

// *** PassEntry Functions to Load and Save the List Encrypted ***

/**
 * Adler32 checksum function. Used to check that encrypted data is correctly
 * decrypted again. data: Pointer to the data to be summed; len is in bytes
 */
static inline uint32_t adler32(uint8_t *data, size_t len)
{
    const uint32_t MOD_ADLER = 65521;
    uint32_t a = 1, b = 0;

    while (len)
    {
	size_t tlen = len > 5550 ? 5550 : len;
	len -= tlen;
	do
	{
	    a += *data++;
	    b += a;
	} while (--tlen);

	a %= MOD_ADLER;
	b %= MOD_ADLER;
    }

    return (b << 16) | a;
}

// *** Base64 Encode and Decoding using wxStrings ***

/** Encode the given binary string into Base64 representation as described in
 * RFC 2045 or RFC 3548. The output string contains only characters
 * [A-Za-z0-9+/] and is roughly 33% longer than the input. The output string
 * can be broken into lines after n characters, where n must be a multiple of
 * 4. The function's code is based on code from the libb64 project (see
 * http://sourceforge.net/projects/libb64).
 *
 * @param instr		input string to encode
 * @param linebreak	break the output string every n characters
 * @return		base64 encoded string
 */
static wxString base64_encode(const char* instr, unsigned int inlen, unsigned int linebreak = 0)
{
    wxString outstr;

    if (inlen == 0) return outstr;

    // calculate output string's size in advance
    unsigned int outsize = (((inlen - 1) / 3) + 1) * 4;
    if (linebreak > 0) outsize += outsize / linebreak;
    outstr.Alloc( outsize );

    static const wxChar encoding64[65]
	= wxT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    char result = 0;
    unsigned int linebegin = 0;
    unsigned int inpos = 0;

    while (1)
    {
	// step 0: if the string is finished here, no padding is needed
	if (inpos == inlen) {
	    return outstr;
	}

	// step 0: process first byte, write first letter
	char fragment = instr[inpos++];
	result = (fragment & 0xFC) >> 2;
	outstr += encoding64[static_cast<int>(result)];
	result = (fragment & 0x03) << 4;

	// step 1: if string finished here, add two padding '='s
	if (inpos == inlen) {
	    outstr += encoding64[static_cast<int>(result)];
	    outstr += '=';
	    outstr += '=';
	    return outstr;
	}

	// step 1: process second byte together with first, write second
	// letter
	fragment = instr[inpos++];
	result |= (fragment & 0xF0) >> 4;
	outstr += encoding64[static_cast<int>(result)];
	result = (fragment & 0x0F) << 2;

	// step 2: if string finished here, add one padding '='
	if (inpos == inlen) {
	    outstr += encoding64[static_cast<int>(result)];
	    outstr += '=';
	    return outstr;
	}

	// step 2: process third byte and write third and fourth letters.
	fragment = instr[inpos++];

	result |= (fragment & 0xC0) >> 6;
	outstr += encoding64[static_cast<int>(result)];

	result  = (fragment & 0x3F) >> 0;
	outstr += encoding64[static_cast<int>(result)];

	// wrap base64 encoding into lines if desired, but only after whole
	// blocks of 4 letters.
	if (linebreak > 0 && outstr.Len() - linebegin >= linebreak)
	{
	    outstr += '\n';
	    linebegin = outstr.Len();
	}
    }
}

/** Decode a string in Base64 representation as described in RFC 2045 or RFC
 * 3548 and return the original data. If a non-whitespace invalid Base64
 * character is encountered _and_ the parameter "strict" is true, then this
 * function will throw a std::runtime_error. If "strict" is false, the
 * character is silently ignored. The function's code is based on code from the
 * libb64 project (see http://sourceforge.net/projects/libb64).
 *
 * @param instr		input string to encode
 * @param strict	throw exception on invalid character
 * @return		decoded binary data
 */
static size_t base64_decode(const wxString& instr, wxMemoryBuffer& outbuff, bool strict = false)
{
    // estimate the output size, assume that the whole input string is
    // base64 encoded.
    outbuff.SetBufSize( instr.Len() * 3 / 4 );
    outbuff.SetDataLen(0);

    // value lookup table: -1 -> exception, -2 -> skip whitespace, -3 = '=' padding
    const char decoding64[256] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -1, -1, -2, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -3, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };

    unsigned int inpos = 0;
    char outchar;
    char fragment;

    while (1)
    {
	// step 0: save first valid letter. do not output a byte, yet.
	do {
	    if (inpos == instr.Len()) return outbuff.GetDataLen();

	    fragment = decoding64[ static_cast<int>(instr[inpos++]) ];

	    if (fragment == -3)
		return outbuff.GetDataLen();

	    if (fragment == -1 && strict)
		throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	} while (fragment < 0);

	outchar = (fragment & 0x3F) << 2;

	// step 1: get second valid letter. output the first byte.
	do {
	    if (inpos == instr.Len()) return outbuff.GetDataLen();

	    fragment = decoding64[ static_cast<int>(instr[inpos++]) ];

	    if (fragment == -3)
		return outbuff.GetDataLen();

	    if (fragment == -1 && strict)
		throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	} while (fragment < 0);

	outchar |= (fragment & 0x30) >> 4;
	outbuff.AppendByte(outchar);

	outchar = (fragment & 0x0F) << 4;

	// step 2: get third valid letter. output the second byte.
	do {
	    if (inpos == instr.Len())  return outbuff.GetDataLen();

	    fragment = decoding64[ static_cast<int>(instr[inpos++]) ];

	    if (fragment == -3)
		return outbuff.GetDataLen();

	    if (fragment == -1 && strict)
		throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	} while (fragment < 0);

	outchar |= (fragment & 0x3C) >> 2;
	outbuff.AppendByte(outchar);

	outchar = (fragment & 0x03) << 6;

	// step 3: get fourth valid letter. output the third byte.
	do {
	    if (inpos == instr.Len()) return outbuff.GetDataLen();

	    fragment = decoding64[ static_cast<int>(instr[inpos++]) ];

	    if (fragment == -3)
		return outbuff.GetDataLen();

	    if (fragment == -1 && strict)
		throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	} while (fragment < 0);

	outchar |= (fragment & 0x3F);
	outbuff.AppendByte(outchar);
    }
}

// *** XTEA New Tiny Encryption Algorithm ***
// Based on Public Domain C Source from
// http://de.wikipedia.org/wiki/XTEA or http://143.53.36.235:8080/source.htm

namespace XTEA
{
/** XTEA block encipher function. Reads two 32-bit unsigned ints from v and
 * writes two 32-bit ints to w. The XTEA key is 128-bit long. */
static void encipher_block(const uint32_t *const v, uint32_t *const w,
			   const uint32_t k[4])
{
    register uint32_t v0 = v[0], v1 = v[1], sum = 0,
	delta = 0x9E3779B9, n = 32;

    while(n-- > 0)
    {
	v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
	sum += delta;
	v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
    }

    w[0] = v0; w[1] = v1;
}

static void decipher_block(const uint32_t *const v, uint32_t *const w,
			   const uint32_t k[4])
{
    register uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720,
	delta = 0x9E3779B9, n = 32;

    /* sum = delta << 5, in general sum = delta * n */

    while(n-- > 0)
    {
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum >> 11) & 3]);
	sum -= delta;
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
    }
   
    w[0] = v0; w[1] = v1;
}

static inline void cbc_copy(uint32_t* a, const uint32_t* b) {
    a[0] = b[0]; a[1] = b[1];
}

static inline void cbc_xor(uint32_t* a, const uint32_t* b) {
    a[0] ^= b[0]; a[1] ^= b[1];
}

static void cbc_encipher(void* cdata, unsigned int cdatalen,
			 const uint32_t key[4], const uint32_t cbciv[2])
{
    uint32_t* data = (uint32_t*)cdata;
    uint32_t cbcv[2];

    assert(cdatalen % 8 == 0);
    size_t datalen = cdatalen / sizeof(uint32_t);

    cbc_copy(cbcv, cbciv);

    for(unsigned int vp = 0; vp < datalen; vp += 2)
    {
	cbc_xor(data + vp, cbcv);
	encipher_block(data + vp, data + vp, key);
	cbc_copy(cbcv, data + vp);
    }
}

static void cbc_decipher(void* cdata, unsigned int cdatalen,
			 const uint32_t key[4], const uint32_t cbciv[2])
{
    uint32_t* data = (uint32_t*)cdata;
    uint32_t cbcv[2], cbcvn[2];

    assert(cdatalen % 8 == 0);
    size_t datalen = cdatalen / sizeof(uint32_t);

    cbc_copy(cbcv, cbciv);

    for(unsigned int vp = 0; vp < datalen ; vp += 2)
    {
	cbc_copy(cbcvn, data + vp);
	decipher_block(data + vp, data + vp, key);
	cbc_xor(data + vp, cbcv);
	cbc_copy(cbcv, cbcvn);
    }
}

} // namespace XTEA

void WPWTutor::loadPasslistFrom(class wxConfigBase& cfg)
{
    for (unsigned int pi = 0; cfg.HasGroup(wxString::Format(_T("pass%d"), pi)) ; ++pi)
    {
	cfg.SetPath( wxString::Format(_T("pass%d"), pi) );

	int tmpint;
	PassEntry pe;

	pe.description = cfg.Read(_T("desc"));
	pe.passtext = cfg.Read(_T("text"));

	cfg.Read(_T("ctime"), &tmpint, 0);
	pe.ctime.Set((time_t)tmpint);

	cfg.Read(_T("ltime"), &tmpint, 0);
	pe.ltime.Set((time_t)tmpint);

	cfg.Read(_T("timespent"), &pe.timespent, 0);
	cfg.Read(_T("rights"), &pe.rights, 0);
	cfg.Read(_T("wrongs"), &pe.wrongs, 0);
	cfg.Read(_T("revealed"), &pe.revealed, 0);

	wxString scores = cfg.Read(_T("scores"), _T(""));
	wxStringTokenizer scoretok(scores, _T(" "));
	while( scoretok.HasMoreTokens() )
	{
	    long score;
	    if (!scoretok.GetNextToken().ToLong(&score)) continue;

	    pe.scores.push_back(score);
	}

	passlist.push_back(pe);
	AppendPassEntry(pe);

	cfg.SetPath(_T(".."));
    }
}

void WPWTutor::savePasslistTo(wxConfigBase& cfg)
{
    for (unsigned int pi = 0; pi < passlist.size(); ++pi)
    {
	cfg.SetPath( wxString::Format(_T("pass%d"), pi) );

	cfg.Write(_T("desc"), passlist[pi].description);
	cfg.Write(_T("text"), passlist[pi].passtext);
	cfg.Write(_T("ctime"), passlist[pi].ctime.GetTicks());
	cfg.Write(_T("ltime"), passlist[pi].ltime.GetTicks());
	cfg.Write(_T("timespent"), passlist[pi].timespent);
	cfg.Write(_T("rights"), passlist[pi].rights);
	cfg.Write(_T("wrongs"), passlist[pi].wrongs);
	cfg.Write(_T("revealed"), passlist[pi].revealed);

	wxString scorelist;
	for(unsigned int i = 0; i < passlist[pi].scores.size(); ++i)
	{
	    if (i == 0) scorelist << passlist[pi].scores[i];
	    else scorelist << _T(" ") << passlist[pi].scores[i];
	}
	cfg.Write(_T("scores"), scorelist);

	cfg.SetPath(_T(".."));
    }
}

void WPWTutor::loadPasslist()
{
    wxConfigBase* cfg = wxConfigBase::Get();

    passlist.clear();
    listctrlPasslist->DeleteAllItems();

    if (cfg->HasGroup(_T("/pwtutor/list")))
    {
	cfg->SetPath(_T("/pwtutor/list"));

	// read base64 encoded data
	wxString base64;
	for (unsigned int ei = 0; cfg->HasEntry(wxString::Format(_T("%d"), ei)) ; ++ei)
	{
	    wxString part64 = cfg->Read(wxString::Format(_T("%d"), ei));
	    base64 += part64;
	}

	wxString adlerstr = cfg->Read(_T("a"));

	// decode base64 data
	wxMemoryBuffer inifile;
	base64_decode(base64, inifile);

	while( inifile.GetDataLen() % 8 != 0 ) inifile.AppendByte(0);

	// decrypt INI-file using XTEA
	const uint32_t key[4] = { 0x78FB89FD, 0x148BDE16, 0x3F48DC71, 0x15377225 };
	const uint32_t cbciv[2] = { 0x21B6167C, 0x7D9A0A92 };

	XTEA::cbc_decipher(inifile.GetData(), inifile.GetDataLen(), key, cbciv);

	unsigned long adler;
	if (!adlerstr.ToULong(&adler) || adler32((uint8_t*)inifile.GetData(), inifile.GetDataLen()) != adler)
	{
	    wxLogError(_("Could not load password list from configuration data."));
	    return;
	}

	// read memory buffer into a wxFileConfig object
	wxMemoryInputStream memin(inifile.GetData(), inifile.GetDataLen());
	wxFileConfig enccfg(memin);

	loadPasslistFrom(enccfg);
    }
}

void WPWTutor::savePasslist()
{
    wxConfigBase* cfg = wxConfigBase::Get();

    cfg->DeleteGroup(_T("/pwtutor/list"));

    if (passlist.size())
    {
	// *** Create Encrypted wxFileConfig object
	wxMemoryOutputStream memout;
	{
	    wxMemoryInputStream memin(NULL, 0);
	    wxFileConfig enccfg(memin);

	    savePasslistTo(enccfg);

	    // write wxFileConfig to wxMemoryOutputStream
	    enccfg.Save(memout);
	}

	// fill stream buffer up to a multiple of 8
	while( memout.GetSize() % 8 != 0 ) memout.PutC(0);

	// copy ini-file data to memory buffer
	wxMemoryBuffer inifile(memout.GetSize());
	size_t copylen = memout.CopyTo(inifile.GetData(), memout.GetSize());
	inifile.SetDataLen(copylen);

	// save checksum of unencrypted ini-file
	uint32_t adler = adler32((uint8_t*)inifile.GetData(), inifile.GetDataLen());

	// encrypt INI-file using XTEA
	const uint32_t key[4] = { 0x78FB89FD, 0x148BDE16, 0x3F48DC71, 0x15377225 };
	const uint32_t cbciv[2] = { 0x21B6167C, 0x7D9A0A92 };

	XTEA::cbc_encipher(inifile.GetData(), inifile.GetDataLen(), key, cbciv);

	// encode into base64 representation
	wxString base64 = base64_encode((char*)inifile.GetData(), inifile.GetDataLen());

	// save into registry/config file

	cfg->SetPath(_T("/pwtutor/list"));

	cfg->Write(_T("a"), wxString::Format(_T("%u"), adler));

	for(unsigned int i = 0; i * 128 < base64.size(); i++)
	{
	    cfg->Write( wxString::Format(_T("%d"), i),
			base64(i*128, 128) );
	}

	cfg->SetPath(_T(".."));
    }

    cfg->Flush();
}

// *** WTaskBarIcon class ***

WTaskBarIcon::WTaskBarIcon(class WPWTutor* wmain)
    : wxTaskBarIcon(),
      ptwmain(wmain)
{
    #include "art/pwtutor-22.h"
    
    tbicon = wxIconFromMemory(pwtutor_22_png);
}

void WTaskBarIcon::Install()
{
    SetIcon(tbicon, _("CryptoTE PWTutor"));
}

void WTaskBarIcon::Remove()
{
    RemoveIcon();
}

wxMenu* WTaskBarIcon::CreatePopupMenu()
{
    wxMenu *menu = new wxMenu;

    menu->Append(myID_RESTORE, _T("&Restore"));

#ifndef __WXMAC_OSX__ /* Mac has built-in quit menu */
    menu->AppendSeparator();
    menu->Append(wxID_EXIT, _T("E&xit"));
#endif

    return menu;
}

void WTaskBarIcon::OnLeftButtonDoubleClick(wxTaskBarIconEvent& WXUNUSED(event))
{
    ptwmain->Show();
    Remove();
}

void WTaskBarIcon::OnMenuRestore(wxCommandEvent& WXUNUSED(event))
{
    ptwmain->Show();
    Remove();
}

void WTaskBarIcon::OnMenuExit(wxCommandEvent& WXUNUSED(event))
{
    ptwmain->Destroy();
}

BEGIN_EVENT_TABLE(WTaskBarIcon, wxTaskBarIcon)
    EVT_TASKBAR_LEFT_DCLICK(WTaskBarIcon::OnLeftButtonDoubleClick)
    EVT_MENU(myID_RESTORE, WTaskBarIcon::OnMenuRestore)
    EVT_MENU(wxID_EXIT, WTaskBarIcon::OnMenuExit)
END_EVENT_TABLE()