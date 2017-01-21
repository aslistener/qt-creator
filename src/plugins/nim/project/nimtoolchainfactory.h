/****************************************************************************
**
** Copyright (C) Filippo Cucchetto <filippocucchetto@gmail.com>
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <projectexplorer/toolchain.h>
#include <projectexplorer/toolchainconfigwidget.h>

namespace Utils { class PathChooser; }

namespace Nim {

class NimToolChain;

class NimToolChainFactory : public ProjectExplorer::ToolChainFactory
{
    Q_OBJECT

public:
    NimToolChainFactory();

    bool canCreate() override;
    ProjectExplorer::ToolChain *create(Core::Id l) override;
    bool canRestore(const QVariantMap &data) override;
    ProjectExplorer::ToolChain *restore(const QVariantMap &data) override;
    QSet<Core::Id> supportedLanguages() const override;
    QList<ProjectExplorer::ToolChain *> autoDetect(const QList<ProjectExplorer::ToolChain *> &alreadyKnown) override;
};

class NimToolChainConfigWidget : public ProjectExplorer::ToolChainConfigWidget
{
    Q_OBJECT

public:
    explicit NimToolChainConfigWidget(NimToolChain *tc);

protected:
    void applyImpl() override;
    void discardImpl() override;
    bool isDirtyImpl() const override;
    void makeReadOnlyImpl() override;

private:
    void fillUI();
    void onCompilerCommandChanged(const QString &path);

    Utils::PathChooser *m_compilerCommand;
    QLineEdit *m_compilerVersion;
};

}
