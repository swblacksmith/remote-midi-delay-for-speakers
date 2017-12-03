using Midi;
using Service.Website.Api.Dtos;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Web.Http;

namespace Service.Website.Api
{
    [RoutePrefix("midi-devices")]
    public class MidiDevicesController : ApiController
    {
        [Route("inputs")]
        public IHttpActionResult GetInputs()
        {
            return Ok(InputDevice.InstalledDevices.Select(Map));
        }

        [Route("outputs")]
        public IHttpActionResult GetOutputs()
        {
            return Ok(OutputDevice.InstalledDevices.Select(Map));
        }

        [Route("inputs/{deviceName}", Name="MidiDeviceInput")]
        public IHttpActionResult GetSpecificInput(string deviceName)
        {
            var inputDevice = InputDevice.InstalledDevices
                .SingleOrDefault(dev => StringComparer.OrdinalIgnoreCase.Equals(dev.Name, deviceName));

            if (inputDevice == null)
            {
                return NotFound();
            }
            
            return Ok(Map(inputDevice));
        }

        [Route("outputs/{deviceName}", Name = "MidiDeviceOutput")]
        public IHttpActionResult GetSpecificOutput(string deviceName)
        {
            var outputDevice = OutputDevice.InstalledDevices
                .SingleOrDefault(dev => StringComparer.OrdinalIgnoreCase.Equals(dev.Name, deviceName));

            if (outputDevice == null)
            {
                return NotFound();
            }

            return Ok(Map(outputDevice));
        }

        private DtoMidiInputDevice Map(InputDevice src)
        {
            var input = new DtoMidiInputDevice();
            Enrich(src, input);
            input.Url = Url.Route("MidiDeviceInput", new { deviceName = src.Name });
            return input;
        }

        private DtoMidiOutputDevice Map(OutputDevice src)
        {
            var output = new DtoMidiOutputDevice();
            Enrich(src, output);
            output.Url = Url.Route("MidiDeviceOutput", new { deviceName = src.Name });
            return output;
        }

        private void Enrich(DeviceBase src, DtoMidiDeviceBase dst)
        {
            dst.Name = src.Name;
        }
    }
}
