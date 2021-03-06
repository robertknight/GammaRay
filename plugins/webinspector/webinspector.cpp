/*
  webinspector.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "webinspector.h"
#include "webviewmodel.h"

#include "include/objecttypefilterproxymodel.h"
#include "include/probeinterface.h"
#include "include/singlecolumnobjectproxymodel.h"

#include <QtPlugin>

using namespace GammaRay;

WebInspector::WebInspector(ProbeInterface *probe, QObject *parent)
  : QObject(parent)
{
  WebViewModel *webViewModel = new WebViewModel(this);
  webViewModel->setSourceModel(probe->objectListModel());
  probe->registerModel("com.kdab.GammaRay.WebPages", webViewModel);

  connect(probe->probe(), SIGNAL(objectCreated(QObject*)), SLOT(objectAdded(QObject*)));

  qputenv("QTWEBKIT_INSPECTOR_SERVER", "0.0.0.0:11733"); // TODO set based on Server address/port
}

void WebInspector::objectAdded(QObject* obj)
{
  // both of the following cases seem to be needed, the web view object changes depending on
  // you have "import QtWebKit.experimental 1.0" or not...
  QObject *experimental = 0;
  if (obj->inherits("QQuickWebView")) {
    experimental = obj->property("experimental").value<QObject*>();
  }
  if (obj->inherits("QQuickWebViewExperimental"))
    experimental = obj;

  if (!experimental)
    return;

  // FIXME: this conversion fails with "QMetaProperty::read: Unable to handle unregistered datatype 'QWebPreferences*' for property 'QQuickWebViewExperimental::preferences'"
  // if we don't have "import QtWebKit.experimental 1.0"
  QObject *prefs = experimental->property("preferences").value<QObject*>();
  if (!prefs)
    return;
  prefs->setProperty("developerExtrasEnabled", true);
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN(WebInspectorFactory)
#endif

#include "webinspector.moc"
