using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Midi;

namespace Service.Website.Api.Dtos.MidiMessages
{
    public class DtoMidiMessageControlChange : DtoMidiChannelMessage
    {
        public override string Type => "cc";

        public byte Control { get; set; }
        public byte Value { get; set; }
    }
}
