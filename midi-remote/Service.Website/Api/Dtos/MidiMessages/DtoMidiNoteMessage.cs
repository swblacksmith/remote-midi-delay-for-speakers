using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api.Dtos.MidiMessages
{
    public abstract class DtoMidiNoteMessage : DtoMidiChannelMessage
    {
        public byte Pitch { get; set; }
        public byte Velocity { get; set; }
    }
}
