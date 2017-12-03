using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Owin.WebSocket;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Service.Website.Api
{
    public class JsonBasedWebSocketConnection : WebSocketConnection
    {
        protected Task SendJson(object obj)
        {
            return SendText(Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(obj, new JsonSerializerSettings() { ContractResolver = new CamelCasePropertyNamesContractResolver() })), true);
        }
    }
}
