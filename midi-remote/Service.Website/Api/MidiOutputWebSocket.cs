using Midi;
using Owin.WebSocket;
using System;
using System.Linq;
using System.Net.WebSockets;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api
{
    internal class MidiOutputWebSocket : JsonBasedWebSocketConnection
    {
        private OutputDevice _outputDevice;

        public MidiOutputWebSocket()
        {

        }

        public override void OnOpen()
        {
            base.OnOpen();
            var outputName = this.Arguments["outputName"];
            _outputDevice = OutputDevice.InstalledDevices.Single(d => StringComparer.OrdinalIgnoreCase.Equals(d.Name, outputName));
            if (!_outputDevice.IsOpen)
            {
                _outputDevice.Open();
            }
        }

        public override Task OnMessageReceived(ArraySegment<byte> message, WebSocketMessageType type)
        {
            //Handle the message from the client

            //Example of JSON serialization with the client
            var json = Encoding.UTF8.GetString(message.Array, message.Offset, message.Count);

            var toSend = Encoding.UTF8.GetBytes(json);

            //Echo the message back to the client as text
            return SendText(toSend, true);
        }
    }
}