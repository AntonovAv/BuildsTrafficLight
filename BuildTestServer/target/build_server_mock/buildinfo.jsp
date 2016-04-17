<%--
  Created by IntelliJ IDEA.
  User: Home
  Date: 25.09.2015
  Time: 3:52
  To change this template use File | Settings | File Templates.
--%>
<%
  String id = request.getParameter("id");
  System.out.println(id);
%>

<%if ("actiTIME_40_Online".equals(id)) {%>
{"count":2,"href":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,running:any","nextHref":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,start:2,running:any","build":[{"id":3119,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1286","status":"SUCCESS","state":"running","running":true,"percentageComplete":13,"href":"/guestAuth/app/rest/builds/id:3119","webUrl":"http://rdbuild/viewLog.html?buildId=3119&buildTypeId=actiTIME_40_Pro"},{"id":3118,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1285","status":"SUCCESS","state":"finished","href":"/guestAuth/app/rest/builds/id:3118","webUrl":"http://rdbuild/viewLog.html?buildId=3118&buildTypeId=actiTIME_40_Pro"}]}
<%} else {%>
<%if("actiTIME_40_b".equals(id)) {%>
{"count":2,"href":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,running:any","nextHref":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,start:2,running:any","build":[{"id":3033,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1220","status":"SUCCESS","state":"running","running":true,"percentageComplete":11,"href":"/guestAuth/app/rest/builds/id:3033","webUrl":"http://rdbuild/viewLog.html?buildId=3033&buildTypeId=actiTIME_40_Pro"},{"id":3032,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1219","status":"FAILURE","state":"finished","href":"/guestAuth/app/rest/builds/id:3032","webUrl":"http://rdbuild/viewLog.html?buildId=3032&buildTypeId=actiTIME_40_Pro"}]}
<%} else if("actiTIME_Sporint_18_Online".equals(id)){%>
{"count":2,"href":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,running:any","nextHref":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,start:2,running:any","build":[{"id":3040,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1227","status":"FAILURE","state":"finished","href":"/guestAuth/app/rest/builds/id:3040","webUrl":"http://rdbuild/viewLog.html?buildId=3040&buildTypeId=actiTIME_40_Pro"},{"id":3039,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1226","status":"FAILURE","state":"finished","href":"/guestAuth/app/rest/builds/id:3039","webUrl":"http://rdbuild/viewLog.html?buildId=3039&buildTypeId=actiTIME_40_Pro"}]}
<%} else {%>
{"count":2,"href":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,running:any","nextHref":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,start:2,running:any","build":[{"id":3119,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1286","status":"SUCCESS","state":"running","running":true,"percentageComplete":13,"href":"/guestAuth/app/rest/builds/id:3119","webUrl":"http://rdbuild/viewLog.html?buildId=3119&buildTypeId=actiTIME_40_Pro"},{"id":3118,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1285","status":"SUCCESS","state":"finished","href":"/guestAuth/app/rest/builds/id:3118","webUrl":"http://rdbuild/viewLog.html?buildId=3118&buildTypeId=actiTIME_40_Pro"}]}

<%--{"count":2,"href":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,running:any","nextHref":"/guestAuth/app/rest/buildTypes/id:actiTIME_40_Pro/builds/?locator=count:2,start:2,running:any","build":[{"id":3119,"buildTypeId":"actiTIME_40_Pro","number":"4_0_Pro_1286","status":"SUCCESS","state":"running","running":true,"percentageComplete":13,"href":"/guestAuth/app/rest/builds/id:3119","webUrl":"http://rdbuild/viewLog.html?buildId=3119&buildTypeId=actiTIME_40_Pro"}
--%>
<%}}%>