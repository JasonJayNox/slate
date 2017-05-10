/*
    Copyright 2016, Mitch Curtis

    This file is part of Slate.

    Slate is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Slate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Slate. If not, see <http://www.gnu.org/licenses/>.
*/

#include "settings.h"

#include <QDebug>
#include <QKeySequence>
#include <QLoggingCategory>
#include <QVector>

Q_LOGGING_CATEGORY(lcSettings, "app.applicationsettings")

ApplicationSettings::ApplicationSettings(QObject *parent) :
    QSettings(parent)
{
    qCDebug(lcSettings) << "Loading settings from" << fileName();
}

QUrl ApplicationSettings::lastProjectUrl() const
{
    return value("lastProjectUrl").toUrl();
}

void ApplicationSettings::setLastProjectUrl(const QUrl &url)
{
    QVariant existingValue = value("lastProjectUrl");
    QUrl existingUrl;
    if (contains("lastProjectUrl")) {
        existingUrl = existingValue.toUrl();
    }

    if (url == existingUrl)
        return;

    setValue("lastProjectUrl", url);
    emit lastProjectUrlChanged();
}

bool ApplicationSettings::loadLastOnStartup() const
{
    return contains("loadLastOnStartup") ? value("loadLastOnStartup").toBool() : defaultLoadLastOnStartup();
}

void ApplicationSettings::setLoadLastOnStartup(bool loadLastOnStartup)
{
    QVariant existingValue = value("loadLastOnStartup");
    bool existingBoolValue = defaultLoadLastOnStartup();
    if (contains("loadLastOnStartup")) {
        existingBoolValue = existingValue.toBool();
    }

    if (loadLastOnStartup == existingBoolValue)
        return;

    setValue("loadLastOnStartup", loadLastOnStartup);
    emit loadLastOnStartupChanged();
}

bool ApplicationSettings::defaultLoadLastOnStartup() const
{
    return false;
}

bool ApplicationSettings::isGridVisible() const
{
    return contains("gridVisible") ? value("gridVisible").toBool() : defaultGridVisible();
}

void ApplicationSettings::setGridVisible(bool gridVisible)
{
    QVariant existingValue = value("gridVisible");
    bool existingBoolValue = defaultGridVisible();
    if (contains("gridVisible")) {
        existingBoolValue = existingValue.toBool();
    }

    if (gridVisible == existingBoolValue)
        return;

    setValue("gridVisible", gridVisible);
    emit gridVisibleChanged();
}

bool ApplicationSettings::defaultGridVisible() const
{
    return true;
}

bool ApplicationSettings::defaultSplitScreen() const
{
    return true;
}

bool ApplicationSettings::isSplitScreen() const
{
    return contains("splitScreen") ? value("splitScreen").toBool() : defaultSplitScreen();
}

void ApplicationSettings::setSplitScreen(bool splitScreen)
{
    QVariant existingValue = value("splitScreen");
    bool existingBoolValue = defaultSplitScreen();
    if (contains("splitScreen")) {
        existingBoolValue = existingValue.toBool();
    }

    if (splitScreen == existingBoolValue)
        return;

    setValue("splitScreen", splitScreen);
    emit splitScreenChanged();
}

bool ApplicationSettings::defaultSplitterLocked() const
{
    return true;
}

bool ApplicationSettings::isSplitterLocked() const
{
    return contains("splitterLocked") ? value("splitterLocked").toBool() : defaultSplitterLocked();
}

void ApplicationSettings::setSplitterLocked(bool splitterLocked)
{
    QVariant existingValue = value("splitterLocked");
    bool existingBoolValue = defaultSplitterLocked();
    if (contains("splitterLocked")) {
        existingBoolValue = existingValue.toBool();
    }

    if (splitterLocked == existingBoolValue)
        return;

    setValue("splitterLocked", splitterLocked);
    emit splitterLockedChanged();
}

bool ApplicationSettings::defaultScrollZoom() const
{
    return true;
}

bool ApplicationSettings::scrollZoom() const
{
    return contains("scrollZoom") ? value("scrollZoom").toBool() : defaultScrollZoom();
}

void ApplicationSettings::setScrollZoom(bool scrollZoom)
{
    QVariant existingValue = value("scrollZoom");
    bool existingBoolValue = defaultScrollZoom();
    if (contains("scrollZoom")) {
        existingBoolValue = existingValue.toBool();
    }

    if (scrollZoom == existingBoolValue)
        return;

    setValue("scrollZoom", scrollZoom);
    emit scrollZoomChanged();
}

void ApplicationSettings::resetShortcutsToDefaults()
{
    static QVector<QString> allShortcuts;
    if (allShortcuts.isEmpty()) {
        allShortcuts.append(QLatin1String("quitShortcut"));
        allShortcuts.append(QLatin1String("newShortcut"));
        allShortcuts.append(QLatin1String("openShortcut"));
        allShortcuts.append(QLatin1String("saveShortcut"));
        allShortcuts.append(QLatin1String("closeShortcut"));
        allShortcuts.append(QLatin1String("revertShortcut"));
        allShortcuts.append(QLatin1String("undoShortcut"));
        allShortcuts.append(QLatin1String("redoShortcut"));
        allShortcuts.append(QLatin1String("centreShortcut"));
        allShortcuts.append(QLatin1String("zoomInShortcut"));
        allShortcuts.append(QLatin1String("zoomOutShortcut"));
        allShortcuts.append(QLatin1String("gridVisibleShortcut"));
        allShortcuts.append(QLatin1String("splitScreenShortcut"));
        allShortcuts.append(QLatin1String("optionsShortcut"));
        allShortcuts.append(QLatin1String("penToolShortcut"));
        allShortcuts.append(QLatin1String("eyeDropperToolShortcut"));
        allShortcuts.append(QLatin1String("eraserToolShortcut"));
        allShortcuts.append(QLatin1String("selectionToolShortcut"));
        allShortcuts.append(QLatin1String("toolModeShortcut"));
        allShortcuts.append(QLatin1String("decreaseToolSizeShortcut"));
        allShortcuts.append(QLatin1String("increaseToolSizeShortcut"));
        allShortcuts.append(QLatin1String("swatchLeftShortcut"));
        allShortcuts.append(QLatin1String("swatchRightShortcut"));
        allShortcuts.append(QLatin1String("swatchUpShortcut"));
        allShortcuts.append(QLatin1String("swatchDownShortcut"));
    }

    foreach (const QString &shortcut, allShortcuts) {
        remove(shortcut);
    }
}

#define GET_SHORTCUT(shortcutName, defaultValueFunction) \
    return contains(shortcutName) ? value(shortcutName).toString() : defaultValueFunction();

#define SET_SHORTCUT(shortcutName, defaultValueFunction, notifySignal) \
    QVariant existingValue = value(shortcutName); \
    QString existingStringValue = defaultValueFunction(); \
    if (contains(shortcutName)) { \
        existingStringValue = existingValue.toString(); \
    } \
    \
    if (shortcut == existingStringValue) \
        return; \
    \
    setValue(shortcutName, shortcut); \
    emit notifySignal();

QString ApplicationSettings::defaultQuitShortcut() const
{
    return QKeySequence(QKeySequence::Quit).toString();
}

QString ApplicationSettings::quitShortcut() const
{
    GET_SHORTCUT("quitShortcut", defaultQuitShortcut)
}
void ApplicationSettings::setQuitShortcut(const QString &shortcut)
{
    SET_SHORTCUT("quitShortcut", defaultQuitShortcut, quitShortcutChanged)
}

QString ApplicationSettings::defaultNewShortcut() const
{
    return QKeySequence(QKeySequence::New).toString();
}

QString ApplicationSettings::newShortcut() const
{
    GET_SHORTCUT("newShortcut", defaultNewShortcut)
}

void ApplicationSettings::setNewShortcut(const QString &shortcut)
{
    SET_SHORTCUT("newShortcut", defaultNewShortcut, newShortcutChanged)
}

QString ApplicationSettings::defaultOpenShortcut() const
{
    return QKeySequence(QKeySequence::Open).toString();
}

QString ApplicationSettings::openShortcut() const
{
    GET_SHORTCUT("openShortcut", defaultOpenShortcut)
}

void ApplicationSettings::setOpenShortcut(const QString &shortcut)
{
    SET_SHORTCUT("openShortcut", defaultOpenShortcut, openShortcutChanged)
}

QString ApplicationSettings::defaultSaveShortcut() const
{
    return QKeySequence(QKeySequence::Save).toString();
}

QString ApplicationSettings::saveShortcut() const
{
    GET_SHORTCUT("saveShortcut", defaultSaveShortcut)
}

void ApplicationSettings::setSaveShortcut(const QString &shortcut)
{
    SET_SHORTCUT("saveShortcut", defaultSaveShortcut, saveShortcutChanged)
}

QString ApplicationSettings::defaultCloseShortcut() const
{
    return QKeySequence(QKeySequence::Close).toString();
}

QString ApplicationSettings::closeShortcut() const
{
    GET_SHORTCUT("closeShortcut", defaultCloseShortcut)
}

void ApplicationSettings::setCloseShortcut(const QString &shortcut)
{
    SET_SHORTCUT("closeShortcut", defaultCloseShortcut, closeShortcutChanged)
}

QString ApplicationSettings::defaultRevertShortcut() const
{
    return QLatin1String("Ctrl+Shift+R");
}

QString ApplicationSettings::revertShortcut() const
{
    GET_SHORTCUT("revertShortcut", defaultRevertShortcut)
}

void ApplicationSettings::setRevertShortcut(const QString &shortcut)
{
    SET_SHORTCUT("revertShortcut", defaultRevertShortcut, revertShortcutChanged)
}

QString ApplicationSettings::defaultUndoShortcut() const
{
    return QKeySequence(QKeySequence::Undo).toString();
}

QString ApplicationSettings::undoShortcut() const
{
    GET_SHORTCUT("undoShortcut", defaultUndoShortcut)
}

void ApplicationSettings::setUndoShortcut(const QString &shortcut)
{
    SET_SHORTCUT("undoShortcut", defaultUndoShortcut, undoShortcutChanged)
}

QString ApplicationSettings::defaultRedoShortcut() const
{
    return QKeySequence(QKeySequence::Redo).toString();
}

QString ApplicationSettings::redoShortcut() const
{
    GET_SHORTCUT("redoShortcut", defaultRedoShortcut)
}

void ApplicationSettings::setRedoShortcut(const QString &shortcut)
{
    SET_SHORTCUT("redoShortcut", defaultRedoShortcut, redoShortcutChanged)
}

QString ApplicationSettings::defaultGridVisibleShortcut() const
{
    return QLatin1String("Ctrl+'");
}

QString ApplicationSettings::gridVisibleShortcut() const
{
    GET_SHORTCUT("gridVisibleShortcut", defaultGridVisibleShortcut)
}

void ApplicationSettings::setGridVisibleShortcut(const QString &shortcut)
{
    SET_SHORTCUT("gridVisibleShortcut", defaultGridVisibleShortcut, gridVisibleShortcutChanged)
}

QString ApplicationSettings::defaultCentreShortcut() const
{
    return QLatin1String("Ctrl+Space");
}

QString ApplicationSettings::centreShortcut() const
{
    GET_SHORTCUT("centreShortcut", defaultCentreShortcut)
}

void ApplicationSettings::setCentreShortcut(const QString &shortcut)
{
    SET_SHORTCUT("centreShortcut", defaultCentreShortcut, centreShortcutChanged)
}

QString ApplicationSettings::defaultZoomInShortcut() const
{
    return QKeySequence(QKeySequence::ZoomIn).toString();
}

QString ApplicationSettings::zoomInShortcut() const
{
    GET_SHORTCUT("zoomInShortcut", defaultZoomInShortcut)
}

void ApplicationSettings::setZoomInShortcut(const QString &shortcut)
{
    SET_SHORTCUT("zoomInShortcut", defaultZoomInShortcut, zoomInShortcutChanged)
}

QString ApplicationSettings::defaultZoomOutShortcut() const
{
    return QKeySequence(QKeySequence::ZoomOut).toString();
}

QString ApplicationSettings::zoomOutShortcut() const
{
    GET_SHORTCUT("zoomOutShortcut", defaultZoomOutShortcut)
}

void ApplicationSettings::setZoomOutShortcut(const QString &shortcut)
{
    SET_SHORTCUT("zoomOutShortcut", defaultZoomOutShortcut, zoomOutShortcutChanged)
}

QString ApplicationSettings::defaultSplitScreenShortcut() const
{
    return QLatin1String("Ctrl+E");
}

QString ApplicationSettings::splitScreenShortcut() const
{
    GET_SHORTCUT("splitScreenShortcut", defaultSplitScreenShortcut)
}

void ApplicationSettings::setSplitScreenShortcut(const QString &shortcut)
{
    SET_SHORTCUT("splitScreenShortcut", defaultSplitScreenShortcut, splitScreenShortcutChanged)
}

QString ApplicationSettings::defaultOptionsShortcut() const
{
    return QLatin1String("Ctrl+Alt+T");
}

QString ApplicationSettings::optionsShortcut() const
{
    GET_SHORTCUT("optionsShortcut", defaultOptionsShortcut)
}

void ApplicationSettings::setOptionsShortcut(const QString &shortcut)
{
    SET_SHORTCUT("optionsShortcut", defaultOptionsShortcut, optionsShortcutChanged)
}

QString ApplicationSettings::defaultPenToolShortcut() const
{
    return QLatin1String("B");
}

QString ApplicationSettings::penToolShortcut() const
{
    GET_SHORTCUT("penToolShortcut", defaultPenToolShortcut)
}

void ApplicationSettings::setPenToolShortcut(const QString &shortcut)
{
    SET_SHORTCUT("penToolShortcut", defaultPenToolShortcut, penToolShortcutChanged)
}

QString ApplicationSettings::defaultEyeDropperToolShortcut() const
{
    return QLatin1String("I");
}

QString ApplicationSettings::eyeDropperToolShortcut() const
{
    GET_SHORTCUT("eyeDropperToolShortcut", defaultEyeDropperToolShortcut)
}

void ApplicationSettings::setEyeDropperToolShortcut(const QString &shortcut)
{
    SET_SHORTCUT("eyeDropperToolShortcut", defaultEyeDropperToolShortcut, eyeDropperToolShortcutChanged)
}

QString ApplicationSettings::defaultEraserToolShortcut() const
{
    return QLatin1String("E");
}

QString ApplicationSettings::eraserToolShortcut() const
{
    GET_SHORTCUT("eraserToolShortcut", defaultEraserToolShortcut)
}

void ApplicationSettings::setEraserToolShortcut(const QString &shortcut)
{
    SET_SHORTCUT("eraserToolShortcut", defaultEraserToolShortcut, eraserToolShortcutChanged)
}

QString ApplicationSettings::defaultSelectionToolShortcut() const
{
    return QLatin1String("M");
}

QString ApplicationSettings::selectionToolShortcut() const
{
    GET_SHORTCUT("selectionToolShortcut", defaultSelectionToolShortcut)
}

void ApplicationSettings::setSelectionToolShortcut(const QString &shortcut)
{
    SET_SHORTCUT("selectionToolShortcut", defaultSelectionToolShortcut, selectionToolShortcutChanged)
}

QString ApplicationSettings::defaultToolModeShortcut() const
{
    return QLatin1String("T");
}

QString ApplicationSettings::toolModeShortcut() const
{
    GET_SHORTCUT("toolModeShortcut", defaultToolModeShortcut)
}

void ApplicationSettings::setToolModeShortcut(const QString &shortcut)
{
    SET_SHORTCUT("toolModeShortcut", defaultToolModeShortcut, toolModeShortcutChanged)
}

QString ApplicationSettings::defaultDecreaseToolSizeShortcut() const
{
    return QLatin1String("[");
}

QString ApplicationSettings::decreaseToolSizeShortcut() const
{
    GET_SHORTCUT("decreaseToolSizeShortcut", defaultDecreaseToolSizeShortcut)
}

void ApplicationSettings::setDecreaseToolSizeShortcut(const QString &shortcut)
{
    SET_SHORTCUT("decreaseToolSizeShortcut", defaultDecreaseToolSizeShortcut, decreaseToolSizeShortcutChanged)
}

QString ApplicationSettings::defaultIncreaseToolSizeShortcut() const
{
    return QLatin1String("]");
}

QString ApplicationSettings::increaseToolSizeShortcut() const
{
    GET_SHORTCUT("increaseToolSizeShortcut", defaultIncreaseToolSizeShortcut)
}

void ApplicationSettings::setIncreaseToolSizeShortcut(const QString &shortcut)
{
    SET_SHORTCUT("increaseToolSizeShortcut", defaultIncreaseToolSizeShortcut, increaseToolSizeShortcutChanged)
}

QString ApplicationSettings::defaultSwatchLeftShortcut() const
{
    return QLatin1String("A");
}

QString ApplicationSettings::swatchLeftShortcut() const
{
    GET_SHORTCUT("swatchLeftShortcut", defaultSwatchLeftShortcut)
}

void ApplicationSettings::setSwatchLeftShortcut(const QString &shortcut)
{
    SET_SHORTCUT("swatchLeftShortcut", defaultSwatchLeftShortcut, swatchLeftShortcutChanged)
}

QString ApplicationSettings::defaultSwatchRightShortcut() const
{
    return QLatin1String("D");
}

QString ApplicationSettings::swatchRightShortcut() const
{
    GET_SHORTCUT("swatchRightShortcut", defaultSwatchRightShortcut)
}

void ApplicationSettings::setSwatchRightShortcut(const QString &shortcut)
{
    SET_SHORTCUT("swatchRightShortcut", defaultSwatchRightShortcut, swatchRightShortcutChanged)
}

QString ApplicationSettings::defaultSwatchUpShortcut() const
{
    return QLatin1String("W");
}

QString ApplicationSettings::swatchUpShortcut() const
{
    GET_SHORTCUT("swatchUpShortcut", defaultSwatchUpShortcut)
}

void ApplicationSettings::setSwatchUpShortcut(const QString &shortcut)
{
    SET_SHORTCUT("swatchUpShortcut", defaultSwatchUpShortcut, swatchUpShortcutChanged)
}

QString ApplicationSettings::defaultSwatchDownShortcut() const
{
    return QLatin1String("S");
}

QString ApplicationSettings::swatchDownShortcut() const
{
    GET_SHORTCUT("swatchDownShortcut", defaultSwatchDownShortcut)
}

void ApplicationSettings::setSwatchDownShortcut(const QString &shortcut)
{
    SET_SHORTCUT("swatchDownShortcut", defaultSwatchDownShortcut, swatchDownShortcutChanged)
}
