package com.google.ctf.sandbox;
public final class BuildConfig {
    public static final String APPLICATION_ID = "com.google.ctf.sandbox";
    public static final String BUILD_TYPE = "debug";
    public static final boolean DEBUG = False;
    public static final String FLAVOR = "";
    public static final int VERSION_CODE = 1;
    public static final String VERSION_NAME = "1.0";

    static BuildConfig()
    {
        com.google.ctf.sandbox.BuildConfig.DEBUG = Boolean.parseBoolean("true");
        return;
    }

    public BuildConfig()
    {
        return;
    }
}
