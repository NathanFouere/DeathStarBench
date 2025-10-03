local _M = {}
local k8s_suffix = os.getenv("fqdn_suffix")
if (k8s_suffix == nil) then
  k8s_suffix = ""
end

function _M.PingTestService()
    local bridge_tracer = require "opentracing_bridge_tracer"
    local ngx = ngx
    local GenericObjectPool = require "GenericObjectPool"
    local TestServiceClient = require "social_network_TestService".TestServiceClient
    local client = GenericObjectPool:connection(
      SocialGraphServiceClient, "social-graph-service" .. k8s_suffix, 9090)
end 

return _M