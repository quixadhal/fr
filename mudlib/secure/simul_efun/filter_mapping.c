varargs mapping filter_mapping(mapping map, string func, mixed ob, mixed extra) {
  mixed *bing;
  mapping ret;	

  ret = ([ ]);
  while ((bing = each(map)) != ({ })) {
    if (call_other(ob, func, extra, bing[0]))
      ret[bing[0]] = bing[1];
  }
  return ret;
} /* filter_mapping() */
