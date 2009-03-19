/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
**************************************************************************/

#ifndef QT4RUNCONFIGURATION_H
#define QT4RUNCONFIGURATION_H

#include <projectexplorer/applicationrunconfiguration.h>
#include <QtCore/QStringList>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE
class QWidget;
class QCheckBox;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

namespace Qt4ProjectManager {

class Qt4Project;

namespace Internal {

class Qt4ProFileNode;



class Qt4RunConfiguration : public ProjectExplorer::ApplicationRunConfiguration
{
    Q_OBJECT
    // to change the name and arguments
    friend class Qt4RunConfigurationWidget;
public:
    Qt4RunConfiguration(Qt4Project *pro, QString proFilePath);
    virtual ~Qt4RunConfiguration();

    virtual QString type() const;
    virtual QWidget *configurationWidget();
    virtual void save(ProjectExplorer::PersistentSettingsWriter &writer) const;
    virtual void restore(const ProjectExplorer::PersistentSettingsReader &reader);

    virtual QString executable() const;
    virtual RunMode runMode() const;
    virtual QString workingDirectory() const;
    virtual QStringList commandLineArguments() const;
    virtual ProjectExplorer::Environment environment() const;

    QString proFilePath() const;

    // TODO detectQtShadowBuild() ? how did this work ?

public slots:
    // This function is called if:
    // X the pro file changes
    // X the active buildconfiguration changes
    // X  the qmake parameters change
    // X  the build directory changes
    void invalidateCachedTargetInformation();

signals:
    void nameChanged(const QString&);
    void commandLineArgumentsChanged(const QString&);
    void runModeChanged(ProjectExplorer::ApplicationRunConfiguration::RunMode runMode);

    // note those signals might not emited for every change
    void effectiveTargetInformationChanged();

private slots:
    void setCommandLineArguments(const QString &argumentsString);
    void nameEdited(const QString&);
    void setRunMode(RunMode runMode);

private:
    void updateTarget();
    QStringList m_commandLineArguments;
    Qt4ProFileNode *m_proFileNode;
    QString m_proFilePath; // Full path to the Application Pro File

    // Cached startup sub project information
    QStringList m_targets;
    QString m_executable;
    QString m_workingDir;
    ProjectExplorer::ApplicationRunConfiguration::RunMode m_runMode;
    bool m_userSetName;
    QWidget *m_configWidget;
    QLabel *m_executableLabel;
    QLabel *m_workingDirectoryLabel;
    bool m_cachedTargetInformationValid;
};

class Qt4RunConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    Qt4RunConfigurationWidget(Qt4RunConfiguration *qt4runconfigration, QWidget *parent);
protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
private slots:
    void setCommandLineArguments(const QString &arguments);
    void nameEdited(const QString &name);
    // TODO connect to signals from qt4runconfiguration for changed arguments and names
    void commandLineArgumentsChanged(const QString &args);
    void nameChanged(const QString &name);
    void runModeChanged(ProjectExplorer::ApplicationRunConfiguration::RunMode runMode);
    void effectiveTargetInformationChanged();
    void termToggled(bool);
private:
    Qt4RunConfiguration *m_qt4RunConfiguration;
    bool m_ignoreChange;
    QLabel *m_executableLabel;
    QLabel *m_workingDirectoryLabel;
    QLineEdit *m_nameLineEdit;
    QLineEdit *m_argumentsLineEdit;
    QCheckBox *m_useTerminalCheck;
    bool m_isShown;
};

class Qt4RunConfigurationFactory : public ProjectExplorer::IRunConfigurationFactory
{
    Q_OBJECT
public:
    Qt4RunConfigurationFactory();
    virtual ~Qt4RunConfigurationFactory();
    virtual bool canCreate(const QString &type) const;
    virtual QSharedPointer<ProjectExplorer::RunConfiguration> create(ProjectExplorer::Project *project, const QString &type);
    QStringList canCreate(ProjectExplorer::Project *pro) const;
    QString nameForType(const QString &type) const;
};

class Qt4RunConfigurationFactoryUser : public ProjectExplorer::IRunConfigurationFactory
{
    Q_OBJECT
public:
    Qt4RunConfigurationFactoryUser();
    virtual ~Qt4RunConfigurationFactoryUser();
    virtual bool canCreate(const QString &type) const;
    virtual QSharedPointer<ProjectExplorer::RunConfiguration> create(ProjectExplorer::Project *project, const QString &type);
    QStringList canCreate(ProjectExplorer::Project *pro) const;
    QString nameForType(const QString &type) const;
};

} // namespace Internal
} // namespace Qt4ProjectManager

#endif // QT4RUNCONFIGURATION_H
