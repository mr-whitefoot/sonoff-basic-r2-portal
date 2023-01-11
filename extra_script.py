Import("env")
env.Replace(PROGNAME="ESP_Sonoff_v%s" % env.GetProjectOption("release_version"))