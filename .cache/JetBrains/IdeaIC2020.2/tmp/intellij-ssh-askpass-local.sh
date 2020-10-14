#!/bin/sh
"/snap/intellij-idea-community/257/jbr/bin/java" -cp "/snap/intellij-idea-community/257/plugins/git4idea/lib/git4idea-rt.jar:/snap/intellij-idea-community/257/lib/xmlrpc-2.0.1.jar:/snap/intellij-idea-community/257/lib/commons-codec-1.14.jar" org.jetbrains.git4idea.nativessh.GitNativeSshAskPassApp "$@"
