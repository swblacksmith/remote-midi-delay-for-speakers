using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api.Dtos.MidiMessages
{
    public abstract class DtoMidiMessage
    {
        public abstract string Type { get; }

        public float Time { get; set; }
    }
}
