using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api.Dtos.MidiMessages
{
    public class DtoMidiMessageNoteOff : DtoMidiNoteMessage
    {
        public override string Type => "off";
    }
}
