#! /bin/sh

BASEDIR=$(dirname $0)

EXPORT_PATH="$BASEDIR/../build-mac/HISSTools_Freeze"
AUDIO_PATH="$HOME/Library/Audio/Plug-Ins"

if [ ! -d "$EXPORT_PATH" ]
then
  mkdir -p "$EXPORT_PATH"
fi

if [ ! -d "$EXPORT_PATH/OSX" ]
then
  mkdir "$EXPORT_PATH/OSX"
fi

cp "$BASEDIR/../manual/HISSTools_Freeze_User_Guide.pdf" "$EXPORT_PATH/" || exit 1

"$BASEDIR/dist-mac-notarize.sh" "$EXPORT_PATH" HISSToolsFreeze.component "$AUDIO_PATH/Components" || exit 1
"$BASEDIR/dist-mac-notarize.sh" "$EXPORT_PATH" HISSToolsFreeze.vst "$AUDIO_PATH/VST" || exit 1
"$BASEDIR/dist-mac-notarize.sh" "$EXPORT_PATH" HISSToolsFreeze.vst3 "$AUDIO_PATH/VST3" || exit 1
