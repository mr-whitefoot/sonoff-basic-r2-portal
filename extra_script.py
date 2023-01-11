Import("env")
env.Replace(PROGNAME="Sonoff_v%s" % env.GetProjectOption("release_version"))