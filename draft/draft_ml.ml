class _Person (name : string) =
  object (this : 'this)
    inherit  Lang.Any.t as super
    method personName = "hehe name"
  end[@@lang.class ]