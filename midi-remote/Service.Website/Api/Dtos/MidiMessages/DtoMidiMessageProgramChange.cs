using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api.Dtos.MidiMessages
{
    public class DtoMidiMessageProgramChange : DtoMidiChannelMessage
    {
        public override string Type => "pc";

        public byte Program { get; set; }
    }
}
