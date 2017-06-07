#include "../../include/sound/MidiSoundGenerator.h"

MidiSoundGenerator::MidiSoundGenerator(RtMidiOut* midiout, uchar channel) : midiout(midiout), channel(channel), prevNote(255) { }

void MidiSoundGenerator::update(const TrackingInfo& tracker) {
    uchar currNote = dynconf.pixel2MidiNote[tracker.current().y];
    cout << (int)currNote << endl;
    // send MIDI message only if note has changed
    if (true) {
        // send note OFF for previous note
        sendMidiMessageForNote(prevNote, OFF);
        // send note ON for new note
        sendMidiMessageForNote(currNote, ON);
        // update prevNote
        prevNote = currNote;
    }
}

void MidiSoundGenerator::sendMidiMessageForNote(uchar midiNote, keypress p) {
    uchar statusByte = (p == ON ? 144 : 128) + channel;

    vector<uchar> message(3);
    message[0] = statusByte;
    message[1] = midiNote;
    message[2] = p == ON ? velocityNoteON : velocityNoteOFF;

    // SLEEP( 500 );
    midiout->sendMessage(&message);
    // SLEEP( 500 );
}
