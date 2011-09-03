/*
  fontmodel.cpp

  This file is part of Endoscope, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2011 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krauss@kdab.com>

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


#include "fontmodel.h"

using namespace Endoscope;

FontModel::FontModel(QObject* parent)
  : QAbstractItemModel(parent)
{

}

QList<QFont> FontModel::currentFonts() const
{
  return m_fonts;
}

void FontModel::updateFonts(const QList<QFont> &fonts)
{
  beginResetModel();
  m_fonts = fonts;
  endResetModel();
}

void FontModel::updateText(const QString& text)
{
  beginResetModel();
  m_text = text;
  endResetModel();
}

QVariant FontModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == 0)
      return "Text";
    if (section == 1)
      return "Font";
    if (section == 2)
      return "Point size";
    if (section == 3)
      return "Bold";
    if (section == 4)
      return "Italic";
    if (section == 5)
      return "Underline";
  }
  return QAbstractItemModel::headerData(section, orientation, role);
}

int FontModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
    return 0;
  return m_fonts.size();
}

QModelIndex FontModel::index(int row, int column, const QModelIndex& parent) const
{
  if (parent.isValid())
    return QModelIndex();
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }
  return createIndex(row, column);
}

QModelIndex FontModel::parent(const QModelIndex& child) const
{
  return QModelIndex();
}

int FontModel::columnCount(const QModelIndex& parent) const
{
  return 6;
}

Qt::ItemFlags FontModel::flags(const QModelIndex& index) const
{
  const Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
  if (index.column() < 2)
    return defaultFlags;
  if (index.column() == 2)
    return defaultFlags | Qt::ItemIsEditable;
  return defaultFlags | Qt::ItemIsUserCheckable;
}

QVariant FontModel::data(const QModelIndex& index, int role) const
{
  if (index.column() == 0) {
    if (role == Qt::DisplayRole)
      return m_text.isEmpty() ? "<no text>" : m_text;
    if (role == Qt::FontRole)
      return m_fonts.at(index.row());
  } else if (index.column() == 1) {
    if (role == Qt::DisplayRole)
      return m_fonts.at(index.row()).family();
  } else if (index.column() == 2) {
    if (role == Qt::DisplayRole || role == Qt::EditRole)
      return m_fonts.at(index.row()).pointSize();
  } else if (index.column() == 3) {
    if (role == Qt::CheckStateRole)
      return m_fonts.at(index.row()).bold() ? Qt::Checked : Qt::Unchecked;
  } else if (index.column() == 4) {
    if (role == Qt::CheckStateRole)
      return m_fonts.at(index.row()).italic() ? Qt::Checked : Qt::Unchecked;
  } else if (index.column() == 5) {
    if (role == Qt::CheckStateRole)
      return m_fonts.at(index.row()).underline() ? Qt::Checked : Qt::Unchecked;
  }

  return QVariant();
}

bool FontModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (index.column() == 2 && role == Qt::EditRole) {
    m_fonts[index.row()].setPointSize(value.toInt());
  } else if (index.column() == 3 && role == Qt::CheckStateRole) {
    m_fonts[index.row()].setBold(value.toInt() == Qt::Checked);
  } else if (index.column() == 4 && role == Qt::CheckStateRole) {
    m_fonts[index.row()].setItalic(value.toInt() == Qt::Checked);
  } else if (index.column() == 5 && role == Qt::CheckStateRole) {
    m_fonts[index.row()].setUnderline(value.toInt() == Qt::Checked);
  }
  const QModelIndex textItem = index.sibling(index.row(), 0);
  emit dataChanged(textItem, textItem);
  return QAbstractItemModel::setData(index, value, role);
}

#include "fontmodel.moc"