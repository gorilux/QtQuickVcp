/****************************************************************************
**
** Copyright (C) 2014 Alexander Rössler
** License: LGPL version 2.1
**
** This file is part of QtQuickVcp.
**
** All rights reserved. This program and the accompanying materials
** are made available under the terms of the GNU Lesser General Public License
** (LGPL) version 2.1 which accompanies this distribution, and is available at
** http://www.gnu.org/licenses/lgpl-2.1.html
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Lesser General Public License for more details.
**
** Contributors:
** Alexander Rössler @ The Cool Tool GmbH <mail DOT aroessler AT gmail DOT com>
**
****************************************************************************/

#ifndef QGCODEPROGRAMMODEL_H
#define QGCODEPROGRAMMODEL_H

#include <QAbstractListModel>
#include <QLinkedList>
#include "qgcodeprogramitem.h"

class QGCodeProgramModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(GCodeProgramRoles)

public:
    class PreviewItem {
    public:
        QModelIndex modelIndex;
        pb::Preview previewItem;
    };

    enum GCodeProgramRoles {
            FileNameRole = Qt::UserRole,
            LineNumberRole,
            GCodeRole,
            SelectedRole,
            ActiveRole,
            ExecutedRole
        };

    explicit QGCodeProgramModel(QObject *parent = 0);
    ~QGCodeProgramModel();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Q_INVOKABLE QVariant getData(const QModelIndex &index, int role) const;
    QModelIndex index(const QString &fileName, int lineNumber) const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QLinkedList<PreviewItem> previewItems() const;

public slots:
    void prepareFile(const QString &fileName, int lineCount);
    void removeFile(const QString &fileName);
    void addLine(const QString &fileName);
    void addPreviewItem(const QModelIndex &index, const pb::Preview &previewItem);
    QVariant data(const QString &fileName, int lineNumber, int role) const;
    bool setData(const QString &fileName, int lineNumber, const QVariant &value, int role);
    void clear();
    void clearPreview(bool update = true);
    void beginUpdate();
    void endUpdate();

private:
    typedef struct {
        int index;
        int count;
    } FileIndex;

    QList<QGCodeProgramItem*> m_items;
    QHash<QString, FileIndex> m_fileIndices;
    QLinkedList<PreviewItem> m_previewItems;

    QVariant internalData(const QModelIndex &index, int role) const;
    bool internalSetData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // QGCODEPROGRAMMODEL_H
