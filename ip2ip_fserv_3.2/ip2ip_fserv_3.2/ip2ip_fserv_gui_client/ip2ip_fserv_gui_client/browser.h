#ifndef __BROWSER__H_
#define __BROWSER__H_
#include <windows.h>
#include <exdisp.h>
#include <exdispid.h>
#include <MsHTML.h>
#include <mshtmhst.h>
#include <commctrl.h>
#include<string.h>
#include<stdio.h>
#pragma comment(lib, "comsupp.lib")

#define BOTTOM 0x9587
#define NOTIMPLEMENTED __asm{ int 3 }; return E_NOTIMPL
extern HWND about;
void DocumentComplete(LPDISPATCH pDisp, VARIANT *url);


class CNullStorage
	: public IStorage
{
	STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	STDMETHODIMP CreateStream(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStream ** ppstm);
	STDMETHODIMP OpenStream(const WCHAR * pwcsName,void * reserved1,DWORD grfMode,DWORD reserved2,IStream ** ppstm);
	STDMETHODIMP CreateStorage(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStorage ** ppstg);
	STDMETHODIMP OpenStorage(const WCHAR * pwcsName,IStorage * pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage ** ppstg);
	STDMETHODIMP CopyTo(DWORD ciidExclude,IID const * rgiidExclude,SNB snbExclude,IStorage * pstgDest);
	STDMETHODIMP MoveElementTo(const OLECHAR * pwcsName,IStorage * pstgDest,const OLECHAR* pwcsNewName,DWORD grfFlags);
	STDMETHODIMP Commit(DWORD grfCommitFlags);
	STDMETHODIMP Revert(void);
	STDMETHODIMP EnumElements(DWORD reserved1,void * reserved2,DWORD reserved3,IEnumSTATSTG ** ppenum);
	STDMETHODIMP DestroyElement(const OLECHAR * pwcsName);
	STDMETHODIMP RenameElement(const WCHAR * pwcsOldName,const WCHAR * pwcsNewName);
	STDMETHODIMP SetElementTimes(const WCHAR * pwcsName,FILETIME const * pctime,FILETIME const * patime,FILETIME const * pmtime);
	STDMETHODIMP SetClass(REFCLSID clsid);
	STDMETHODIMP SetStateBits(DWORD grfStateBits,DWORD grfMask);
	STDMETHODIMP Stat(STATSTG * pstatstg,DWORD grfStatFlag);
};


class CMyFrame
	: public IOleInPlaceFrame
{
public:
	STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	STDMETHODIMP GetWindow(HWND FAR* lphwnd);
	STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode);
	STDMETHODIMP GetBorder(LPRECT lprectBorder);
	STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS pborderwidths);
	STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS pborderwidths);
	STDMETHODIMP SetActiveObject(IOleInPlaceActiveObject *pActiveObject,LPCOLESTR pszObjName);
	STDMETHODIMP InsertMenus(HMENU hmenuShared,LPOLEMENUGROUPWIDTHS lpMenuWidths);
	STDMETHODIMP SetMenu(HMENU hmenuShared,HOLEMENU holemenu,HWND hwndActiveObject);
	STDMETHODIMP RemoveMenus(HMENU hmenuShared);
	STDMETHODIMP SetStatusText(LPCOLESTR pszStatusText);
	STDMETHODIMP EnableModeless(BOOL fEnable);
	STDMETHODIMP TranslateAccelerator(  LPMSG lpmsg,WORD wID);
};

class CMySite
	: public IOleClientSite,
	public IOleInPlaceSite
{
	STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	STDMETHODIMP SaveObject();
	STDMETHODIMP GetMoniker(DWORD dwAssign,DWORD dwWhichMoniker,IMoniker ** ppmk);
	STDMETHODIMP GetContainer(LPOLECONTAINER FAR* ppContainer);
	STDMETHODIMP ShowObject();
	STDMETHODIMP OnShowWindow(BOOL fShow);
	STDMETHODIMP RequestNewObjectLayout();
	STDMETHODIMP GetWindow(HWND FAR* lphwnd);
	STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode);
	STDMETHODIMP CanInPlaceActivate();
	STDMETHODIMP OnInPlaceActivate();
	STDMETHODIMP OnUIActivate();
	STDMETHODIMP GetWindowContext(LPOLEINPLACEFRAME FAR* lplpFrame,LPOLEINPLACEUIWINDOW FAR* lplpDoc,LPRECT lprcPosRect,LPRECT lprcClipRect,LPOLEINPLACEFRAMEINFO lpFrameInfo);
	STDMETHODIMP Scroll(SIZE scrollExtent);
	STDMETHODIMP OnUIDeactivate(BOOL fUndoable);
	STDMETHODIMP OnInPlaceDeactivate();
	STDMETHODIMP DiscardUndoState();
	STDMETHODIMP DeactivateAndUndo();
	STDMETHODIMP OnPosRectChange(LPCRECT lprcPosRect);
};


class CMyContainer
	: public IOleContainer
{
	STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	STDMETHODIMP ParseDisplayName(IBindCtx *pbc,LPOLESTR pszDisplayName,ULONG *pchEaten,IMoniker **ppmkOut);
	STDMETHODIMP EnumObjects(DWORD grfFlags,IEnumUnknown **ppenum);
	STDMETHODIMP LockContainer(BOOL fLock);
};

class AdviseSink:public DWebBrowserEvents2
{
public:

	STDMETHODIMP QueryInterface(REFIID riid,void ** ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP GetTypeInfoCount(UINT *pctInfo);
	STDMETHODIMP GetTypeInfo(UINT itInfo, LCID lcid, ITypeInfo **ppTypeInfo);
	STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID);
	STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,
		VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);
	STDMETHODIMP_(VOID *) getThis();
private:
	ULONG		 m_cRefs;	
};

class DocHostUIHandler:public IDocHostUIHandler
{
public:
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	STDMETHODIMP_(HRESULT) ShowContextMenu(DWORD dwID,
		POINT *point,
		IUnknown *pcmdtReserved,
		IDispatch *pdispReserved);
	STDMETHODIMP_(HRESULT) GetHostInfo(DOCHOSTUIINFO *pInfo);
	STDMETHODIMP_(HRESULT) ShowUI(DWORD dwID,
		IOleInPlaceActiveObject *pActiveObject,
		IOleCommandTarget *pCommandTarget,
		IOleInPlaceFrame *pFrame,
		IOleInPlaceUIWindow *pDoc);
	STDMETHODIMP_(HRESULT) HideUI();
	STDMETHODIMP_(HRESULT) UpdateUI();
	STDMETHODIMP_(HRESULT) EnableModeless(int fEnable);
	STDMETHODIMP_(HRESULT) OnDocWindowActivate(int fActivate);
	STDMETHODIMP_(HRESULT) OnFrameWindowActivate(int fActivate);
	STDMETHODIMP_(HRESULT) ResizeBorder(LPCRECT prcBorder,
		IOleInPlaceUIWindow *pUIWindow,
		BOOL fRameWindow);
	STDMETHODIMP_(HRESULT) TranslateAccelerator(LPMSG lpMsg,
		const GUID *pguidCmdGroup,
		DWORD nCmdID);
	STDMETHODIMP_(HRESULT) GetOptionKeyPath(LPOLESTR *pchKey, DWORD dw);
	STDMETHODIMP_(HRESULT) GetDropTarget(IDropTarget *pDropTarget,
		IDropTarget **ppDropTarget);
	STDMETHODIMP_(HRESULT) GetExternal(IDispatch **ppDispatch);
	STDMETHODIMP_(HRESULT) TranslateUrl(DWORD dwTranslate,
		OLECHAR *pchUrlIn,
		OLECHAR **pchUrlOut);
	STDMETHODIMP_(HRESULT) FilterDataObject(IDataObject *pDO, 
		IDataObject **ppDORet);
	STDMETHODIMP_(VOID *) getThis();
};

IWebBrowser2* iBrowser = NULL;
CNullStorage storage;
CMySite site;
CMyFrame frame;
IOleObject *mpWebObject;
AdviseSink *sink; 
bool done = false;
DocHostUIHandler *docHostUIHandler = NULL;


STDMETHODIMP CNullStorage::QueryInterface(REFIID riid,void ** ppvObject)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP_(ULONG) CNullStorage::AddRef(void)
{
	return 1;
}

STDMETHODIMP_(ULONG) CNullStorage::Release(void)
{
	return 1;
}

STDMETHODIMP CNullStorage::CreateStream(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStream ** ppstm)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::OpenStream(const WCHAR * pwcsName,void * reserved1,DWORD grfMode,DWORD reserved2,IStream ** ppstm)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::CreateStorage(const WCHAR * pwcsName,DWORD grfMode,DWORD reserved1,DWORD reserved2,IStorage ** ppstg)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::OpenStorage(const WCHAR * pwcsName,IStorage * pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage ** ppstg)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::CopyTo(DWORD ciidExclude,IID const * rgiidExclude,SNB snbExclude,IStorage * pstgDest)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::MoveElementTo(const OLECHAR * pwcsName,IStorage * pstgDest,const OLECHAR* pwcsNewName,DWORD grfFlags)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::Commit(DWORD grfCommitFlags)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::Revert(void)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::EnumElements(DWORD reserved1,void * reserved2,DWORD reserved3,IEnumSTATSTG ** ppenum)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::DestroyElement(const OLECHAR * pwcsName)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::RenameElement(const WCHAR * pwcsOldName,const WCHAR * pwcsNewName)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::SetElementTimes(const WCHAR * pwcsName,FILETIME const * pctime,FILETIME const * patime,FILETIME const * pmtime)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::SetClass(REFCLSID clsid)
{
	return S_OK;
}

STDMETHODIMP CNullStorage::SetStateBits(DWORD grfStateBits,DWORD grfMask)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CNullStorage::Stat(STATSTG * pstatstg,DWORD grfStatFlag)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::QueryInterface(REFIID riid,void ** ppvObject)
{
	if(riid == IID_IUnknown || riid == IID_IOleClientSite)
		*ppvObject = (IOleClientSite*)this;
	else if(riid == IID_IOleInPlaceSite)
		*ppvObject = (IOleInPlaceSite*)this;
	else if(riid == IID_IDocHostUIHandler)
	{
		docHostUIHandler = new DocHostUIHandler;
		*ppvObject = (IDocHostUIHandler*)docHostUIHandler->getThis();
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	return S_OK;
}

STDMETHODIMP_(ULONG) CMySite::AddRef(void)
{
	return 1;
}

STDMETHODIMP_(ULONG) CMySite::Release(void)
{
	return 1;
}

STDMETHODIMP CMySite::SaveObject()
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::GetMoniker(DWORD dwAssign,DWORD dwWhichMoniker,IMoniker ** ppmk)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::GetContainer(LPOLECONTAINER FAR* ppContainer)
{
	*ppContainer = NULL;

	return E_NOINTERFACE;
}

STDMETHODIMP CMySite::ShowObject()
{
	return NOERROR;
}

STDMETHODIMP CMySite::OnShowWindow(BOOL fShow)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::RequestNewObjectLayout()
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::GetWindow(HWND FAR* lphwnd)
{
	*lphwnd = about;

	return S_OK;
}

STDMETHODIMP CMySite::ContextSensitiveHelp(BOOL fEnterMode)
{
	NOTIMPLEMENTED;
}


STDMETHODIMP CMySite::CanInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP CMySite::OnInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP CMySite::OnUIActivate()
{
	return S_OK;
}

STDMETHODIMP CMySite::GetWindowContext(
									   LPOLEINPLACEFRAME FAR* ppFrame,
									   LPOLEINPLACEUIWINDOW FAR* ppDoc,
									   LPRECT prcPosRect,
									   LPRECT prcClipRect,
									   LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	*ppFrame = &frame;
	*ppDoc = NULL;
	GetClientRect(about,prcPosRect);
	GetClientRect(about,prcClipRect);

	lpFrameInfo->fMDIApp = FALSE;
	lpFrameInfo->hwndFrame = about;
	lpFrameInfo->haccel = NULL;
	lpFrameInfo->cAccelEntries = 0;

	return S_OK;
}

STDMETHODIMP CMySite::Scroll(SIZE scrollExtent)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::OnUIDeactivate(BOOL fUndoable)
{
	return S_OK;
}

STDMETHODIMP CMySite::OnInPlaceDeactivate()
{
	return S_OK;
}

STDMETHODIMP CMySite::DiscardUndoState()
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::DeactivateAndUndo()
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMySite::OnPosRectChange(LPCRECT lprcPosRect)
{
	return S_OK;
}


STDMETHODIMP CMyFrame::QueryInterface(REFIID riid,void ** ppvObject)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP_(ULONG) CMyFrame::AddRef(void)
{
	return 1;
}

STDMETHODIMP_(ULONG) CMyFrame::Release(void)
{
	return 1;
}

// IOleWindow
STDMETHODIMP CMyFrame::GetWindow(HWND FAR* lphwnd)
{
	*lphwnd = about;
	return S_OK;
}

STDMETHODIMP CMyFrame::ContextSensitiveHelp(BOOL fEnterMode)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::GetBorder(LPRECT lprectBorder)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::RequestBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::SetBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::SetActiveObject(IOleInPlaceActiveObject *pActiveObject,LPCOLESTR pszObjName)
{
	return S_OK;
}

STDMETHODIMP CMyFrame::InsertMenus(HMENU hmenuShared,LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::SetMenu(HMENU hmenuShared,HOLEMENU holemenu,HWND hwndActiveObject)
{
	return S_OK;
}

STDMETHODIMP CMyFrame::RemoveMenus(HMENU hmenuShared)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP CMyFrame::SetStatusText(LPCOLESTR pszStatusText)
{
	return S_OK;
}

STDMETHODIMP CMyFrame::EnableModeless(BOOL fEnable)
{
	return S_OK;
}

STDMETHODIMP CMyFrame::TranslateAccelerator(  LPMSG lpmsg,WORD wID)
{
	NOTIMPLEMENTED;
}

STDMETHODIMP AdviseSink::QueryInterface(REFIID riid,void ** ppv)
{
	*ppv = NULL;

	if ((riid == IID_IUnknown) || (riid == IID_IDispatch) ||
		(riid == DIID_DWebBrowserEvents2))
	{
		*ppv = (LPVOID)this;
	}
	else
		return E_NOINTERFACE;

	((LPUNKNOWN)*ppv)->AddRef();

	return NOERROR;
}

STDMETHODIMP_(ULONG) AdviseSink::AddRef()
{
	return m_cRefs++;
}

STDMETHODIMP_(ULONG) AdviseSink::Release()
{
	return m_cRefs--;
}

STDMETHODIMP AdviseSink::GetTypeInfoCount(UINT *pctInfo) {

	*pctInfo = 1;
	return NOERROR;
}

STDMETHODIMP AdviseSink::GetTypeInfo(UINT itInfo, LCID lcid, ITypeInfo **ppTypeInfo) 
{
	NOTIMPLEMENTED;
}

STDMETHODIMP AdviseSink::GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID) {

	HRESULT hRes;
	ITypeInfo *pInfo;

	if (riid != IID_NULL)
		return ResultFromScode(DISP_E_UNKNOWNINTERFACE);


	hRes = GetTypeInfo(0, lcid, &pInfo);

	if (FAILED(hRes))
		return hRes;


	hRes = pInfo->GetIDsOfNames(rgszNames, cNames, rgDispID);

	pInfo->Release();

	return hRes;
}

STDMETHODIMP AdviseSink::Invoke(DISPID dispIdMember, 
								REFIID riid, 
								LCID lcid, 
								WORD wFlags,
								DISPPARAMS* pDispParams, 
								VARIANT* pVarResult,
								EXCEPINFO* pExcepInfo, 
								UINT* puArgErr)
{

	if (!pDispParams)
		return DISP_E_PARAMNOTOPTIONAL;

	switch (dispIdMember)
	{
	case DISPID_DOCUMENTCOMPLETE:
		{
			if (!done)
			{
				IDispatch *disp = NULL;
				DocumentComplete(disp, pVarResult);
			}
		}
		return S_OK;

	case DISPID_NAVIGATECOMPLETE2:
		return S_OK;

	default:
		return DISP_E_MEMBERNOTFOUND;

	}

	return S_OK;
}

STDMETHODIMP_(VOID *) AdviseSink::getThis()
{
	return this;
}

STDMETHODIMP DocHostUIHandler::QueryInterface(REFIID riid, void **ppv)
{
	*ppv = NULL;

	if ((riid == IID_IUnknown) || (riid == IID_IDocHostUIHandler))
	{
		*ppv = (LPVOID)this;
	}
	else
		return E_NOINTERFACE;

	((LPUNKNOWN)*ppv)->AddRef();

	return NOERROR;
}

STDMETHODIMP_(ULONG) DocHostUIHandler::AddRef()
{
	return 1;
}

STDMETHODIMP_(ULONG) DocHostUIHandler::Release()
{
	return 1;
}

STDMETHODIMP_(HRESULT) DocHostUIHandler::ShowContextMenu(DWORD dwID,
														 POINT *point,
														 IUnknown *pcmdtReserved,
														 IDispatch *pdispReserved)
{
	return S_FALSE;
}

STDMETHODIMP_(HRESULT) DocHostUIHandler::GetHostInfo(DOCHOSTUIINFO *pInfo)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::ShowUI(DWORD dwID,
												IOleInPlaceActiveObject *pActiveObject,
												IOleCommandTarget *pCommandTarget,
												IOleInPlaceFrame *pFrame,
												IOleInPlaceUIWindow *pDoc)
{
	return S_FALSE;
}					            
STDMETHODIMP_(HRESULT) DocHostUIHandler::HideUI()
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::UpdateUI()
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::EnableModeless(int fEnable)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::OnDocWindowActivate(int fActivate)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::OnFrameWindowActivate(int fActivate)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::ResizeBorder(LPCRECT prcBorder,
													  IOleInPlaceUIWindow *pUIWindow,
													  BOOL fRameWindow)
{
	return S_FALSE;
}           						
STDMETHODIMP_(HRESULT) DocHostUIHandler::TranslateAccelerator(LPMSG lpMsg,
															  const GUID *pguidCmdGroup,
															  DWORD nCmdID)
{
	return S_FALSE;
}					          
STDMETHODIMP_(HRESULT) DocHostUIHandler::GetOptionKeyPath(LPOLESTR *pchKey, DWORD dw)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::GetDropTarget(IDropTarget *pDropTarget,
													   IDropTarget **ppDropTarget)
{
	return S_FALSE;
}								
STDMETHODIMP_(HRESULT) DocHostUIHandler::GetExternal(IDispatch **ppDispatch)
{
	return S_FALSE;
}
STDMETHODIMP_(HRESULT) DocHostUIHandler::TranslateUrl(DWORD dwTranslate,
													  OLECHAR *pchUrlIn,
													  OLECHAR **pchUrlOut)
{
	return S_FALSE;
}								
STDMETHODIMP_(HRESULT) DocHostUIHandler::FilterDataObject(IDataObject *pDO, 
														  IDataObject **ppDORet)
{
	return S_FALSE;
}					
STDMETHODIMP_(VOID *) DocHostUIHandler::getThis()
{
	return this;
}			


BSTR ptr = 0;

class mxBrowser {

public:

	mxBrowser() {
		ptr = L"http://lostsidedead.com";
	}

	mxBrowser(BSTR site_ptr) {
		ptr = site_ptr;
	}
	void ResizeWindow(int x, int y, int w, int h) {
		if(mpWebObject)
		{
			RECT rect = {x,y,w,h};
			IOleInPlaceObject *pInPlaceObject = NULL;
			iBrowser->QueryInterface(IID_IOleInPlaceObject,
				(void**)&pInPlaceObject);   	        if (pInPlaceObject)
				if (pInPlaceObject)
				{
					pInPlaceObject->SetObjectRects(&rect, &rect);
					pInPlaceObject->Release();
				}
		}
	}

	void ResizeWindow(RECT *rect) {

		if(mpWebObject)
			{
				IOleInPlaceObject *pInPlaceObject = NULL;
				//GetClientRect(about,rect); 
				iBrowser->QueryInterface(IID_IOleInPlaceObject,
					(void**)&pInPlaceObject);   	        if (pInPlaceObject)
					if (pInPlaceObject)
					{
						pInPlaceObject->SetObjectRects(rect, rect);
						pInPlaceObject->Release();
					}
			}
	}
	void Sink(IOleObject *pElem, IUnknown *pUnk)
	{
		HRESULT hr;
		IConnectionPointContainer* pCPC = NULL;
		IConnectionPoint* pCP = NULL;
		DWORD dwCookie;

		hr = pElem->QueryInterface( IID_IConnectionPointContainer, (void**)&pCPC );
		if ( SUCCEEDED(hr) )        
		{
			hr = pCPC->FindConnectionPoint( DIID_DWebBrowserEvents2, &pCP );
			if ( SUCCEEDED(hr) )           
			{
				hr = pCP->Advise( pUnk, &dwCookie );
				if ( SUCCEEDED(hr) )              
				{
				}
				pCP->Release();
			}
			pCPC->Release();        
		}
	}


	int startBrowser()
	{
		RECT rect; 
		VARIANT vURL; 
		IOleInPlaceObject *pInPlaceObject = NULL; 
		OleCreate(CLSID_WebBrowser,IID_IOleObject,OLERENDER_DRAW,
			0,&site,&storage,(void**)&mpWebObject);

		mpWebObject->SetHostNames(L"Web Host",L"Web View");
		GetClientRect(about,&rect);
		mpWebObject->DoVerb(OLEIVERB_SHOW,NULL,&site,-1,about,&rect);
		mpWebObject->QueryInterface(IID_IWebBrowser2,(void**)&iBrowser);

		sink = new AdviseSink;
		IUnknown *pUnk = NULL;
		pUnk = (IUnknown *)sink->getThis();

		Sink(mpWebObject, pUnk);

		iBrowser->QueryInterface(IID_IOleInPlaceObject,
			(void**)&pInPlaceObject);   	        
		if (pInPlaceObject)
		{
			pInPlaceObject->SetObjectRects(&rect, &rect);
			pInPlaceObject->Release();
		}

		vURL.vt = VT_BSTR;
		vURL.bstrVal = SysAllocString(L"about:blank");
		iBrowser->Navigate2(&vURL, NULL, NULL, NULL, NULL);

		VariantClear(&vURL);
		ViewSite(ptr);
		return 0;
	}

	int scrollDown(IDispatch *pDisp, int n)
	{
		HRESULT hr;

		IHTMLDocument2 *pDocument = NULL;
		hr = pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pDocument);
		if( (FAILED(hr)) || !pDocument)
		{
			MessageBox(NULL, "QueryInterface failed", "WebBrowser", MB_OK);
			return S_OK;
		}

		IHTMLElement *pBody = NULL;
		hr = pDocument->get_body( &pBody );
		if( (!SUCCEEDED(hr)) || !pBody)
		{
			MessageBox(NULL, "get_body failed", "WebBrowser", MB_OK);
			return S_OK;
		}

		IHTMLElement2 *pElement = NULL;
		hr = pBody->QueryInterface(IID_IHTMLElement2, (void**)&pElement);
		if( !SUCCEEDED(hr) || !pElement)
		{
			MessageBox(NULL, "QueryInterface failed", "WebBrowser", MB_OK);
			return S_OK;
		}
		if ( n != BOTTOM)
			pElement->put_scrollTop(n);
		else
		{
			long scrollHeight;
			pElement->get_scrollHeight(&scrollHeight);
			pElement->put_scrollTop(scrollHeight);
		}
		pElement->Release();
		pDocument->Release();
		return 0;
	}

	HRESULT LoadWebBrowserFromStream(IWebBrowser2 *pWebBrowser, IStream *pStream)
	{
		HRESULT hr;
		IDispatch *pHtmlDoc = NULL;
		IPersistStreamInit *pPersistStreamInit = NULL;

		hr = pWebBrowser->get_Document(&pHtmlDoc);
		if( SUCCEEDED(hr) )
		{
			scrollDown(pHtmlDoc, 100);
			hr = pHtmlDoc->QueryInterface(IID_IPersistStreamInit, (void**)&pPersistStreamInit);
			if( SUCCEEDED(hr) )
			{	
				hr = pPersistStreamInit->InitNew();
				if( SUCCEEDED(hr) )
				{
					hr = pPersistStreamInit->Load(pStream);
				}
			}
		}
		return 0;
	}

	void ViewSite(BSTR ptr) {
		iBrowser->Navigate(ptr,NULL,NULL,NULL,NULL);
	}

	void ViewSite2(VARIANT *var) {
		iBrowser->Navigate2(var,NULL,NULL,NULL,NULL);
	}

	void Stop() {
		iBrowser->Stop();
	}

	void Forward() {
		iBrowser->GoForward();
	}

	void Back() {
		iBrowser->GoBack();
	}
};

void DocumentComplete(LPDISPATCH pDisp, VARIANT *url)
{
	if(!done)
	{
		done = true;

		HRESULT hr;
		IUnknown *pUnkBrowser = NULL;
		IUnknown *pUnkDisp = NULL;
		IStream *pStream = NULL;

		hr = iBrowser->QueryInterface(IID_IUnknown, (void**)&pUnkBrowser);
		if( SUCCEEDED(hr) )
		{
			if( SUCCEEDED(hr) )
			{
				pUnkBrowser->Release();
			}


		}
	}
}


#endif
