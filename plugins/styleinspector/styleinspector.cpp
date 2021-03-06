/*
  styleinspector.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "styleinspector.h"
#include "complexcontrolmodel.h"
#include "controlmodel.h"
#include "pixelmetricmodel.h"
#include "primitivemodel.h"
#include "standardiconmodel.h"

#include "include/objecttypefilterproxymodel.h"
#include "include/probeinterface.h"
#include "include/singlecolumnobjectproxymodel.h"

#include <ui/palettemodel.h>
#include <common/network/objectbroker.h>

#include <QApplication>
#include <QItemSelectionModel>

using namespace GammaRay;

StyleInspector::StyleInspector(ProbeInterface *probe, QObject *parent)
  : StyleInspectorInterface(parent),
    m_primitiveModel(new PrimitiveModel(this)),
    m_controlModel(new ControlModel(this)),
    m_complexControlModel(new ComplexControlModel(this)),
    m_pixelMetricModel(new PixelMetricModel(this)),
    m_standardIconModel(new StandardIconModel(this)),
    m_standardPaletteModel(new PaletteModel(this))
{
  ObjectTypeFilterProxyModel<QStyle> *styleFilter = new ObjectTypeFilterProxyModel<QStyle>(this);
  styleFilter->setSourceModel(probe->objectListModel());
  SingleColumnObjectProxyModel *singleColumnProxy = new SingleColumnObjectProxyModel(this);
  singleColumnProxy->setSourceModel(styleFilter);
  probe->registerModel("com.kdab.GammaRay.StyleList", singleColumnProxy);

  QItemSelectionModel *selectionModel = ObjectBroker::selectionModel(singleColumnProxy);
  connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
          this, SLOT(styleSelected(QItemSelection)));

  probe->registerModel("com.kdab.GammaRay.StyleInspector.PrimitiveModel", m_primitiveModel);
  probe->registerModel("com.kdab.GammaRay.StyleInspector.ControlModel", m_controlModel);
  probe->registerModel("com.kdab.GammaRay.StyleInspector.ComplexControlModel", m_complexControlModel);
  probe->registerModel("com.kdab.GammaRay.StyleInspector.PixelMetricModel", m_pixelMetricModel);
  probe->registerModel("com.kdab.GammaRay.StyleInspector.StandardIconModel", m_standardIconModel);
  probe->registerModel("com.kdab.GammaRay.StyleInspector.PaletteModel", m_standardPaletteModel);
}

StyleInspector::~StyleInspector()
{
}

void StyleInspector::styleSelected(const QItemSelection &selection)
{
  if (selection.isEmpty())
    return;
  const QModelIndex index = selection.first().topLeft();
  QObject *obj = index.data(ObjectModel::ObjectRole).value<QObject*>();
  QStyle *style = qobject_cast<QStyle*>(obj);
  m_primitiveModel->setStyle(style);
  m_controlModel->setStyle(style);
  m_complexControlModel->setStyle(style);
  m_pixelMetricModel->setStyle(style);
  m_standardIconModel->setStyle(style);
  m_standardPaletteModel->setPalette(style ? style->standardPalette() : qApp->palette());
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN(StyleInspectorFactory)
#endif

#include "styleinspector.moc"
