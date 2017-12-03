using Midi;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Owin.WebSocket;
using Service.Website.Api.Dtos.MidiMessages;
using System;
using System.Linq;
using System.Net.WebSockets;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api
{
    public class MidiInputWebSocket : JsonBasedWebSocketConnection
    {
        private InputDevice _inputDevice;

        public MidiInputWebSocket()
        {

        }

        public override void OnOpen()
        {
            base.OnOpen();
            var inputName = this.Arguments["inputName"];
            _inputDevice = InputDevice.InstalledDevices.Single(d => StringComparer.OrdinalIgnoreCase.Equals(d.Name, inputName));
            if (!_inputDevice.IsOpen)
            {
                _inputDevice.Open();
            }
            if (!_inputDevice.IsReceiving)
            {
                _inputDevice.StartReceiving(null);
            }
            _inputDevice.ControlChange += InputDevice_ControlChange;
            _inputDevice.ProgramChange += InputDevice_ProgramChange;
            _inputDevice.NoteOn += InputDevice_NoteOn;
            _inputDevice.NoteOff += InputDevice_NoteOff;
        }

        private void InputDevice_ControlChange(ControlChangeMessage msg)
        {
            SendJson(Map(msg));
        }

        private void InputDevice_ProgramChange(ProgramChangeMessage msg)
        {
            SendJson(Map(msg));
        }

        private void InputDevice_NoteOn(NoteOnMessage msg)
        {
            SendJson(Map(msg));
        }

        private void InputDevice_NoteOff(NoteOffMessage msg)
        {
            SendJson(Map(msg));
        }

        private DtoMidiMessageControlChange Map(ControlChangeMessage msg)
        {
            var cc = new DtoMidiMessageControlChange();

            EnrichChannelMessage(msg, cc);
            cc.Control = Convert.ToByte(msg.Control);
            cc.Value = Convert.ToByte(msg.Value);

            return cc;
        }

        private DtoMidiMessageProgramChange Map(ProgramChangeMessage msg)
        {
            var pc = new DtoMidiMessageProgramChange();

            EnrichChannelMessage(msg, pc);
            pc.Program = Convert.ToByte(msg.Instrument);

            return pc;
        }

        private DtoMidiMessageNoteOn Map(NoteOnMessage msg)
        {
            var on = new DtoMidiMessageNoteOn();

            EnrichNoteMessage(msg, on);

            return on;
        }

        private DtoMidiMessageNoteOff Map(NoteOffMessage msg)
        {
            var off = new DtoMidiMessageNoteOff();

            EnrichNoteMessage(msg, off);

            return off;
        }

        private void EnrichNoteMessage(NoteMessage msg, DtoMidiNoteMessage on)
        {
            EnrichChannelMessage(msg, on);
            on.Pitch = Convert.ToByte(msg.Pitch);
            on.Velocity = Convert.ToByte(msg.Velocity);
        }

        private void EnrichChannelMessage(ChannelMessage src, DtoMidiChannelMessage dst)
        {
            dst.Channel = Convert.ToByte(src.Channel);
            EnrichMessage(src, dst);
        }

        private void EnrichMessage(DeviceMessage src, DtoMidiMessage dst)
        {
            dst.Time = src.Time;
        }

/*        public override Task OnMessageReceived(ArraySegment<byte> message, WebSocketMessageType type)
        {
            //Handle the message from the client

            //Example of JSON serialization with the client
            var json = Encoding.UTF8.GetString(message.Array, message.Offset, message.Count);

            var toSend = Encoding.UTF8.GetBytes(json);

            //Echo the message back to the client as text
            return SendText(toSend, true);
        }*/

        public override void OnClose(WebSocketCloseStatus? closeStatus, string closeStatusDescription)
        {
            base.OnClose(closeStatus, closeStatusDescription);

            if (_inputDevice != null)
            {
                _inputDevice.ControlChange -= InputDevice_ControlChange;
                _inputDevice.ProgramChange -= InputDevice_ProgramChange;
                _inputDevice.NoteOn -= InputDevice_NoteOn;
                _inputDevice.NoteOff -= InputDevice_NoteOff;
            }
        }
    }
}