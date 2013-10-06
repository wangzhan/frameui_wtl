/**
 * @file    client_handler.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once
#include "cef_ptr.h"
#include "cef_client.h"
#include "cef_life_span_handler.h"
#include "cef_v8context_handler.h"
#include "cef_browser.h"
#include "cef_win.h"


/**
 * @class   ClientHandler
 * @brief   ClientHandler implementation
 */
class ClientHandler : public CefClient,
                      public CefLifeSpanHandler,
                      public CefV8ContextHandler
{
 public:
  ClientHandler();
  virtual ~ClientHandler();

  // CefClient methods
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
    return this;
  }

  virtual CefRefPtr<CefV8ContextHandler> GetV8ContextHandler() OVERRIDE {
    return this;
  }

  // CefLifeSpanHandler methods
  virtual bool OnBeforePopup(CefRefPtr<CefBrowser> parentBrowser,
                             const CefPopupFeatures& popupFeatures,
                             CefWindowInfo& windowInfo,
                             const CefString& url,
                             CefRefPtr<CefClient>& client,
                             CefBrowserSettings& settings) OVERRIDE;
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  // CefV8ContextHandler methods
  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefV8Context> context) OVERRIDE;


  void SetMainHwnd(CefWindowHandle hwnd);
  CefWindowHandle GetMainHwnd() { return m_MainHwnd; }
  CefWindowHandle GetBrowserHwnd() { return m_BrowserHwnd; }

  std::string GetStartupURL() const { return m_StartupURL; }

  void CloseMainWindow();

 protected:

  // The child browser window
  CefRefPtr<CefBrowser> m_Browser;

  // The main frame window handle
  CefWindowHandle m_MainHwnd;

  // The child browser window handle
  CefWindowHandle m_BrowserHwnd;

  // The URL to be loaded at application startup.
  std::string m_StartupURL;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(ClientHandler);
  // Include the default locking implementation.
  IMPLEMENT_LOCKING(ClientHandler);
};
